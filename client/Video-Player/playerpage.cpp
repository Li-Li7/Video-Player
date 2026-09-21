#include "playerpage.h"
#include "ui_playerpage.h"
#include <QMouseEvent>
#include "login.h"
#include "toast.h"
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
    // 显⽰⾳量调节窗⼝
    connect(ui->volumeBtn, &QPushButton::clicked, this, &PlayerPage::onVolumeBtnClicked);
    playSpeed = new PlaySpeed(this);
    // 绑定倍数播放按钮信号槽
    connect(ui->speedBtn, &QPushButton::clicked, this, &PlayerPage::onSpeedBtnClicked);
    // 点赞
    connect(ui->likeImageBtn, &QPushButton::clicked, this, &PlayerPage::onLkeImageBtnClcked);


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

void PlayerPage::onVolumeBtnClicked()
{
    moveWindows(mapToGlobal(QPoint(0, 0)));
    volume->show();
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


// void PlayerPage::onPlayBtnClicked()
// {

// }
