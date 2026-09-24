#include "bulletscreenitem.h"
#include <QHBoxLayout>

BulletScreenItem::BulletScreenItem(QWidget *parent)
    : QFrame{parent}
{
    setObjectName("bulletScreenWnd");
    this->setFixedHeight(38);
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    // 弹幕中⽤⼾头像
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(30, 30);
    imageLabel->setScaledContents(true);
    imageLabel->hide(); // 默认情况下不展⽰⽤⼾头像
    // 弹幕中⽂本
    textLabel = new QLabel(this);
    textLabel->setStyleSheet("font-family : 微软雅⿊;"
                        "font-size : 18px;"
                        "color : #FFFFFF;"
                        "border : none;");
    textLabel->adjustSize();
    // 将元素添加到⽔平布局器中
    hLayout->addWidget(imageLabel);
    hLayout->addWidget(textLabel);
    hLayout->setContentsMargins(10, 4, 19, 4);
    hLayout->setSpacing(8);

}


void BulletScreenItem::setBulletScreenText(const QString &content)
{
    textLabel->setText(content);
    textLabel->adjustSize();
}

void BulletScreenItem::setBulletScreenIcon(QPixmap &pixmap)
{
    imageLabel->setPixmap(pixmap);
    imageLabel->show();
    this->setStyleSheet("#bulletScreenWnd{"
                        "border : 1px solid #3ECEFE;"
                        "border-radius : 19px;}");

}

void BulletScreenItem::setBulletScreenAnimal(int x, int duration)
{
    animal = new QPropertyAnimation(this, "pos");
    animal->setDuration(duration);
    animal->setStartValue(QPoint(x, 0));
    animal->setEndValue(QPoint(0 - this->width(), 0));
    connect(animal, &QPropertyAnimation::finished, this, [&]{delete this;});
}

void BulletScreenItem::startAnimal()
{
    show();
    animal->start();
}
