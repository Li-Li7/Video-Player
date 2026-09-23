#include "playslider.h"
#include "ui_playslider.h"
#include <QMouseEvent>
#include "util.h"

PlaySlider::PlaySlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PlaySlider)
{
    ui->setupUi(this);
    playProgress=0;
}

PlaySlider::~PlaySlider()
{
    delete ui;
}

void PlaySlider::setPlayStep(double stepRatio)
{
    playProgress = stepRatio*ui->inLine->width();
    LOG()<<playProgress;
    moveSlider();
}

void PlaySlider::mousePressEvent(QMouseEvent *event)
{
    // 当鼠标左键按下时，需要记录当前鼠标的x位置，即播放当前进度
    if(event->button() == Qt::LeftButton)
    {
        playProgress = event->pos().x();
        moveSlider();
        return;
    }

    QWidget::mousePressEvent(event);
}

void PlaySlider::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        playProgress = event->pos().x();
        moveSlider();

        emit setPlayProgress((double)playProgress/ui->inLine->width());
        return;
    }
    QWidget::mouseReleaseEvent(event);
}

void PlaySlider::mouseMoveEvent(QMouseEvent *event)
{
    // 检测鼠标的位置是否在播放进度条窗口中
    if(!this->geometry().contains(event->pos()))
    {
        LOG()<<event->pos();
        return;
    }

    // 鼠标的位置在进度条窗口中
    if(event->buttons() == Qt::LeftButton){
        playProgress = event->pos().x();

        if(playProgress < 0){
            playProgress = 0;
        }

        int maxWidth = this->width();
        if(playProgress > maxWidth){
            playProgress = maxWidth;
        }

        moveSlider();
        return;
    }
    QWidget::mouseMoveEvent(event);
}



void PlaySlider::moveSlider()
{
    ui->outLine->setGeometry(ui->outLine->x(), ui->outLine->y(), playProgress, ui->outLine->height());
}
