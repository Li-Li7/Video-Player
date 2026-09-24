#include "playerpage.h"
#include "ui_playerpage.h"
#include <QMouseEvent>
#include <QTimer>
#include "login.h"
#include "toast.h"
#include <QShortcut>
PlayerPage::PlayerPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlayerPage)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_ShowModal);

    connect(ui->minBtn,&QPushButton::clicked,this,&QWidget::showMinimized);
    connect(ui->quitBtn,&QPushButton::clicked,this,&QWidget::close);
    connect(ui->glBtn,&QPushButton::toggled,this,[this](bool checked){
        if(checked)
        {
            isGlobalMode = false;
            setWindowFlags(Qt::Widget);  // 设置为普通窗口
            show();  // 重新显示窗口使标志生效
        }
        else
        {
            isGlobalMode = true;
            setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
            show();  // 重新显示窗口使标志生效
        }
    });

    volume = new Volume(this);

    playSpeed = new PlaySpeed(this);
    // 绑定倍数播放按钮信号槽
    connect(ui->speedBtn, &QPushButton::clicked, this, &PlayerPage::onSpeedBtnClicked);
    // 点赞
    connect(ui->likeImageBtn, &QPushButton::clicked, this, &PlayerPage::onLkeImageBtnClcked);
    // 播放
    connect(ui->playBtn, &QPushButton::clicked, this,&PlayerPage::onPlayBtnClicked);
    // 设置倍速播放
    connect(playSpeed, &PlaySpeed::setPlaySpeed, this,&PlayerPage::onPlaySpeedChanged);
    // 设置⾳量
    connect(volume, &Volume::setVolume, this, &PlayerPage::setVolume);
    ui->volumeBtn->setCheckable(true);          // 点击切静音
    ui->volumeBtn->installEventFilter(this);    // 按钮侧悬浮
    volume->installEventFilter(this);           // 弹窗侧悬浮
    hideTimer = new QTimer(this);
    hideTimer->setSingleShot(true);
    hideTimer->setInterval(220);                // 经验值，实机微调
    connect(hideTimer, &QTimer::timeout, this, [this]{
        auto hovering = [](QWidget* w){
            return w->isVisible() &&
                   w->rect().contains(w->mapFromGlobal(QCursor::pos()));
        };
        if (!hovering(ui->volumeBtn) && !hovering(volume) && !volume->isDragging())
            volume->hide();
    });
    connect(ui->volumeBtn, &QPushButton::toggled, this, [this](bool muted){
        if (mpvPlayer) mpvPlayer->setMute(muted);
    });

    // 点击进度条，设置播放进度
    connect(ui->videoSlider, &PlaySlider::setPlayProgress, this,&PlayerPage::setPlayProgress);

    // 播放按钮绑定空格快捷键
    QShortcut* shortcur = new QShortcut(ui->playBtn);
    QKeySequence keySequence(" ");
    shortcur->setKey(keySequence);
    connect(shortcur, &QShortcut::activated, this, [=](){ui->playBtn->animateClick();});

    // 弹幕区域布局
    initBarrageArea();


}

PlayerPage::~PlayerPage()
{
    delete ui;
}

void PlayerPage::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
    {
        QWidget::mousePressEvent(event);
        return;
    }
    QPoint globalPos = event->globalPosition().toPoint();

    // 1. 判断是否在可拖动区域（鼠标点转局部坐标，嵌套层级再多也准确）
    bool inPlayHead = ui->playHead->rect().contains(ui->playHead->mapFromGlobal(globalPos));


    if (!inPlayHead) {
        QWidget::mousePressEvent(event);
        return;
    }

    // 2. 在拖动区域内：判断点击的是不是按钮
    QWidget* child = childAt(event->position().toPoint());
    bool isButton = false;
    if (child)
    {
        // 包含自定义 PageSwitchButton（继承自 QPushButton）
        isButton = child->metaObject()->inherits(&QPushButton::staticMetaObject);
    }
    //
    // 点击到按钮：透传事件，不启动拖动
    if (isButton) {
        QWidget::mousePressEvent(event);
        return;
    }

    // 3. 点击空白/标题/容器：启动拖动
    isDragging = true;
    dragPos = globalPos - frameGeometry().topLeft();
    grabMouse();
    setCursor(Qt::SizeAllCursor);
    event->accept();
}



void PlayerPage::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && isDragging) {
        QPoint targetPos = event->globalPosition().toPoint() - dragPos;
        move(targetPos);
        event->accept();
        return;
    }

    QWidget::mouseMoveEvent(event);
}

void PlayerPage::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isDragging)
    {
        isDragging = false;
        releaseMouse();
        unsetCursor();
    }
    QWidget::mouseReleaseEvent(event);
}

void PlayerPage::moveWindows(const QPoint &point)
{
    QPoint newPoint = point + QPoint(this->width() - volume->width() - 13,533);
    volume->move(newPoint);

    newPoint = point + QPoint(this->width() - playSpeed->width() - 82, 536);
    playSpeed->move(newPoint);

}

void PlayerPage::startPlaying(const QString &videoFilePath)
{
    if (!mpvPlayer) {                                    // ← 关键：只创建一次
        mpvPlayer = new MpvPlayer(ui->screen, this);

        // 连接也只建立一次
        connect(mpvPlayer, &MpvPlayer::playPositionChanged,
                this, &PlayerPage::onPlayPositionChanged);

        connect(mpvPlayer, &MpvPlayer::durationChanged, this, [this](int64_t d){
            if (d > 0) duration = d;                     // 拿到真实总时长
        });

        connect(mpvPlayer, &MpvPlayer::endOfPlaylist, this, [this]{
            isEnded = true;                              // 播完标志，见第二节
            isPlay  = false;
            ui->playBtn->setStyleSheet("border-image : url(:/images/PlayPage/zanting.png)");
        });
    }

    this->videoFilePath = videoFilePath;
    isEnded = false;
    mpvPlayer->startPlay(videoFilePath);
    mpvPlayer->pause();
}

void PlayerPage::onPlayPositionChanged(int64_t playTime)
{
    if (ui->videoSlider->isUserDragging()) return;
    this->playTime = playTime;
    ui->videoDuration->setText(secondToTime(playTime) + "/" + secondToTime(duration));

    // 修改进度条
    if (duration > 0)
    {
        ui->videoSlider->setPlayStep((double)playTime / duration);
    }

    // 当播放结束时，设置播放按钮为暂停状态
    if(this->playTime == duration)
    {
        // 视频播放完毕，更新播放按钮图标
         // 此时播放按钮应该变为暂停
        isPlay = false;
        ui->playBtn->setStyleSheet("border-image : url(:/images/PlayPage/zanting.png)");
    }
}

void PlayerPage::setPlayProgress(double playRatio)
{
    if (!mpvPlayer || duration <= 0) return;
    playTime = (int64_t)(playRatio * duration);
    mpvPlayer->setCurrentPlayPositon(playTime);
}

void PlayerPage::loadBulletScreenData()
{
    QList<BulletScreenInfo> bulletScreenList;
    // 构造弹幕数据-不同时间点弹幕,1 2 3秒钟，每秒⼀条弹幕
    for(int i = 0; i < 3; ++i)
    {
        BulletScreenInfo bsItem("1000001", i+1, "我是弹幕"+QString::number(i));
        bulletScreenList.append(bsItem);
        bulletScreenLists.insert(bsItem.playTime, bulletScreenList);
        bulletScreenList.clear();
    }

    // 构造弹幕数据-相同时间点弹幕
    for(int i = 0; i < 4; ++i){
        BulletScreenInfo bsItem("1000001", 5, "我是弹幕"+QString::number(4+i));
        bulletScreenList.append(bsItem);
    }
    bulletScreenLists.insert(bulletScreenList[0].playTime, bulletScreenList);


}



void PlayerPage::onSpeedBtnClicked()
{
    moveWindows(mapToGlobal(QPoint(0, 0)));
    playSpeed->show();
}

void PlayerPage::onLkeImageBtnClcked()
{
    // 检测⽤⼾是否登录，登录时才能点赞
    // Login* login = new Login();
    // login->show();
    Toast::showMessage("用户对视频点赞");
    Login* login=new Login(this);
    Toast::showMessage("先登录，再点赞",login);


}


void PlayerPage::onPlayBtnClicked()
{
    isPlay = !isPlay;
    if(isPlay){
        ui->playBtn->setStyleSheet("border-image : url(:/images/PlayPage/bofang.png);");
        mpvPlayer->play();
    }else{
        ui->playBtn->setStyleSheet("border-image : url(:/images/PlayPage/zanting.png);");
        mpvPlayer->pause();
    }

    // 播放完毕，再⼀次点击播放按钮时，重新开始播放
    if(playTime == 52 && isPlay)
    {
        // 播放位置修改到起始为⽌，⽤⼾点击播放按钮可以重新播放
        this->playTime = 0;
        startPlaying(videoFilePath);
        mpvPlayer->play();
    }


    // 如果本次播放中，视频的播放数未更新时候再去更新
    // if(!isUpdatePlayNum)
    // {
    //     updatePlayNumer();
    // }
}

void PlayerPage::onPlaySpeedChanged(double speed)
{
    mpvPlayer->setPlaySpeed(speed);
}

void PlayerPage::setVolume(int volumeRatio)
{
    mpvPlayer->setVolume(volumeRatio);
}

bool PlayerPage::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->volumeBtn || watched == volume)
    {
        if (event->type() == QEvent::Enter) {
            hideTimer->stop();                        // 关键：取消隐藏
            if (watched == ui->volumeBtn) {
                moveWindows(mapToGlobal(QPoint(0, 0)));
                volume->show();
                volume->raise();
            }
        } else if (event->type() == QEvent::Leave) {
            hideTimer->start();                       // 不立即隐藏
        }
    }
    return QWidget::eventFilter(watched, event);
}

QString PlayerPage::secondToTime(int64_t second)
{
    QString time;
    // ⼩时存在时才显⽰
    if(second/60/60)
    {
        time += QString::asprintf("%02lld:", second/60/60);
    }
    // 拼接上分和秒
    time += QString::asprintf("%02lld:%02lld",second/60,second%60);
    return time;

}

void PlayerPage::initBarrageArea()
{
    // 创建弹幕的显⽰区域对话框，该对话框没有边框，背景透明
    barrageArea = new QDialog(this);
    barrageArea->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    barrageArea->setAttribute(Qt::WA_TranslucentBackground);
    barrageArea->setMinimumSize(this->width(), 38*3);
    // 垂直布局器，添加到对话框中
    QVBoxLayout* layout = new QVBoxLayout(barrageArea);
    barrageArea->setLayout(layout);
    // 在弹幕区域添加⽤来显⽰三⾏弹幕的控件
    top = new QFrame(this);
    top->setFixedSize(this->width(), 38);
    middle = new QFrame(this);
    middle->setFixedSize(this->width(), 38);
    bottom = new QFrame(this);
    bottom->setFixedSize(this->width(), 38);
    layout->addWidget(top);
    layout->addWidget(middle);
    layout->addWidget(bottom);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    // 移动弹幕窗⼝到播放窗⼝的head底下
    QPoint point = mapToGlobal(QPoint(0, 0));
    point.setY(point.y() + ui->playHead->height());
    barrageArea->move(point);
    barrageArea->show();

}
