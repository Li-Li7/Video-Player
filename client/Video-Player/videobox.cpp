#include "videobox.h"
#include "ui_videobox.h"
#include "util.h"
#include <QDir>

VideoBox::VideoBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoBox)
{
    ui->setupUi(this);
    //默认隐藏删除按钮
    ui->delVideoBtn->hide();

    playerPage = new PlayerPage();

    //封面与标题安装事件过滤器
    ui->imageBox->installEventFilter(this);
    ui->videoTitle->installEventFilter(this);
}

VideoBox::~VideoBox()
{
    delete ui;
}

bool VideoBox::eventFilter(QObject *watched, QEvent *event)
{
    if(ui->imageBox==watched||ui->videoTitle==watched)
    {
        if(event->type()==QEvent::MouseButtonPress)
        {
            // LOG()<<"打开播放窗口";
            playerPage->show();
            onPlayBtnClicked();
            return true;
        }
    }
    return QObject::eventFilter(watched,event);
}

void VideoBox::onPlayBtnClicked()
{
    playerPage->show();
    // mpv库测试,视频放在当前⽬录下videos⽬录中
    QDir dir = QDir::current(); // qtcreate中拿到的是exe所在⽬录
    dir.cdUp();
    dir.cdUp();
    QString videoPath = dir.absolutePath();
    videoPath += "/videos/trailer.mp4";
    playerPage->startPlaying(videoPath);

}

