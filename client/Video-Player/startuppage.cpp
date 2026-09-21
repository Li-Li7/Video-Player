#include "startuppage.h"
#include <QLabel>
#include <QFile>
#include <QTimer>

StartUpPage::StartUpPage(QDialog *parent)
    : QDialog{parent}
{
    setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(1450,860);
    setStyleSheet("background-color:#FFFFFF");

    //窗口显示图片
    QLabel* imageLabel=new QLabel(this);
    QPixmap pix(":/images/startupPage/myshipin.png");
    imageLabel->setPixmap(QPixmap(pix));
    int centerX = (width() - pix.width()) / 2;
    int centerY = (height() - pix.height()) / 2;
    imageLabel->move(centerX, centerY);



}

void StartUpPage::startTimer()
{
    QTimer* timer=new QTimer();
    //在时间到达之后重复发出timeout信号
    timer->setSingleShot(false);
    connect(timer,&QTimer::timeout,this,[=](){
        if(loginSuccess&&myselfInfoSuccess)
        {
            timer->stop();
            delete timer;
            close();
        }
    });
    timer->start(2000);
}

