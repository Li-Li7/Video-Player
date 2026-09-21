#include "VideoPlayer.h"
#include "ui_videoplayer.h"
#include <QGraphicsDropShadowEffect>
#include<QMouseEvent>

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);
    initUI();
    connectSigalAndSlot();
    ui->glBtn->setCheckable(true);  // 设置为可切换

}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}

VideoPlayer* VideoPlayer::instance=nullptr;
VideoPlayer *VideoPlayer::getInstance()
{
    if(nullptr==instance)
    {
        instance=new VideoPlayer();
    }
    return instance;
}

void VideoPlayer::onSwitchPage(int pageId)
{
    qDebug() << "切换页面:" << pageId; // 能打印说明信号槽正常，问题在页面本身
    ui->stackedWidget->setCurrentIndex(pageId);
    resetswitchBtnInfo(pageId);
}

void VideoPlayer::initUI()
{
    //去除窗口的边框
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    //设置窗口图标
    setWindowIcon(QIcon(":/images/homePage/logo.png"));
    //窗口添加阴影效果
    QGraphicsDropShadowEffect* dropShadow=new QGraphicsDropShadowEffect(this);
    dropShadow->setColor(Qt::black);
    dropShadow->setBlurRadius(5);
    dropShadow->setOffset(0,0);
    // setGraphicsEffect(dropShadow);
    ui->playerBg->setGraphicsEffect(dropShadow);

    //设置页面切换按钮的文本和图片
    ui->homePageBtn->setTextColor("#000000");
    ui->homePageBtn->setImageAndText(":/images/homePage/shouyexuan.png", "首页",HomePage);
    ui->myPageBtn->setTextColor("#999999");
    ui->myPageBtn->setImageAndText(":/images/homePage/wode.png", "我的",MyselfPage);
    ui->sysPageBtn->setTextColor("#999999");
    ui->sysPageBtn->setImageAndText(":/images/homePage/admin.png", "系统",AdminPage);
}

void VideoPlayer::connectSigalAndSlot()
{
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

    connect(ui->homePageBtn,&PageSwitchButton::switchPage,this,&VideoPlayer::onSwitchPage);
    connect(ui->myPageBtn,&PageSwitchButton::switchPage,this,&VideoPlayer::onSwitchPage);
    connect(ui->sysPageBtn,&PageSwitchButton::switchPage,this,&VideoPlayer::onSwitchPage);

    //我的页面切换到上传视频页面
    connect(ui->myPage, &MyselfWidget::switchUploadVideoPage, this, [=](int pageId){
        LOG()<<"切换到上传视频⻚⾯";
        onSwitchPage(pageId);
    });

    // 视频上传⻚⾯切换到我的⻚⾯
    connect(ui->uploadVideo, &UploadVideoPage::switchMySelfPage, this, [=](int pageId){
                VideoPlayer::onSwitchPage(pageId);
            });

}

void VideoPlayer::resetswitchBtnInfo(int pageId)
{
    // 重新设置bodyLeft中按钮上的文本和图片的高亮
    // 设置文本的颜色
    QList<PageSwitchButton*> switchBtns = findChildren<PageSwitchButton*>();
    for(auto& switchBtn : switchBtns)
    {
        if(switchBtn->getPageId() != pageId){
            switchBtn->setTextColor("#999999");
        }
    }

    // 设置按钮的图片
    if(pageId == HomePage){
        // 在HomePageBtn的图片设置为高亮
        // 将MyselfPageBtn、AdminPageBtn的图片设置为灰色
        ui->homePageBtn->setImage(":/images/homePage/shouyexuan.png");
        ui->myPageBtn->setImage(":/images/homePage/wode.png");
        ui->sysPageBtn->setImage(":/images/homePage/admin.png");
        // 修复版（已注释，未删除）：原路径缺 .png，图标加载失败
        // ui->sysPageBtn->setImage(":/images/homePage/admin.png");
    }else if(pageId == MyselfPage){
        ui->homePageBtn->setImage(":/images/homePage/shouye.png");
        ui->myPageBtn->setImage(":/images/homePage/wodexuan.png");
        ui->sysPageBtn->setImage(":/images/homePage/admin.png");
        // 修复版（已注释，未删除）：
        // ui->sysPageBtn->setImage(":/images/homePage/admin.png");
    }else if(pageId == AdminPage){
        ui->homePageBtn->setImage(":/images/homePage/shouye.png");
        ui->myPageBtn->setImage(":/images/homePage/wode.png");
        ui->sysPageBtn->setImage(":/images/homePage/adminxuan.png");
        // 修复版（已注释，未删除）：
        // ui->sysPageBtn->setImage(":/images/homePage/adminxuan.png");
    }else{
        LOG()<<"暂不支持的页面";
    }
}



void VideoPlayer::mousePressEvent(QMouseEvent *event)
{
    // 只处理左键
    if (event->button() != Qt::LeftButton) {
        QWidget::mousePressEvent(event);
        return;
    }

    QPoint globalPos = event->globalPosition().toPoint();

    // 1. 判断是否在可拖动区域（鼠标点转局部坐标，嵌套层级再多也准确）
    bool inHead = ui->head->rect().contains(ui->head->mapFromGlobal(globalPos));
    bool inBodyLeft = ui->bodyLeft->rect().contains(ui->bodyLeft->mapFromGlobal(globalPos));
    bool inDragArea = inHead || inBodyLeft;

    if (!inDragArea) {
        QWidget::mousePressEvent(event);
        return;
    }

    // 2. 在拖动区域内：判断点击的是不是按钮
    QWidget* child = childAt(event->position().toPoint());
    bool isButton = false;
    if (child) {
        // 包含自定义 PageSwitchButton（继承自 QPushButton）
        isButton = child->metaObject()->inherits(&QPushButton::staticMetaObject);
    }

    // 点击到按钮：透传事件，不启动拖动
    if (isButton) {
        QWidget::mousePressEvent(event);
        return;
    }

    // 3. 点击空白/标题/容器：启动拖动
    m_isDragging = true;
    m_dragPos = globalPos - frameGeometry().topLeft();
    grabMouse();
    setCursor(Qt::SizeAllCursor);
    event->accept();
}

void VideoPlayer::mouseMoveEvent(QMouseEvent *event)
{
    // 只有左键按下 + 拖动状态，才移动窗口，不再重复判断区域
    if ((event->buttons() & Qt::LeftButton) && m_isDragging) {
        QPoint targetPos = event->globalPosition().toPoint() - m_dragPos;
        move(targetPos);
        event->accept();
        return;
    }

    QWidget::mouseMoveEvent(event);
}

void VideoPlayer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isDragging) {
        m_isDragging = false;
        releaseMouse();
        unsetCursor();
    }
    QWidget::mouseReleaseEvent(event);
}









