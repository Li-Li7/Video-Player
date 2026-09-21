#include "videoplayer.h"

#include <QApplication>

#include "startuppage.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //先显示启动页面
    StartUpPage startupPage;
    startupPage.startTimer();
    startupPage.exec();


    //程序的主界面
    VideoPlayer* videoplayer=VideoPlayer::getInstance();
    videoplayer->show();
    // BitPlayer实例通过getInstance获取
    VideoPlayer* videoPlayer = VideoPlayer::getInstance();
    videoPlayer->show();
    return a.exec();
    return QApplication::exec();
}
