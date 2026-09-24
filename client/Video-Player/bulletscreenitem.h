#ifndef BULLETSCREENITEM_H
#define BULLETSCREENITEM_H

#include <QFrame>
#include <QLabel>
#include <QPropertyAnimation>

class BulletScreenItem : public QFrame
{

    Q_OBJECT
public:
    // 完成弹幕显⽰布局
    explicit BulletScreenItem(QWidget *parent = nullptr);
    // 设置弹幕中⽂本 头像
    void setBulletScreenText(const QString &content);
    void setBulletScreenIcon(QPixmap& pixmap);

    // 给弹幕添加动画
    void setBulletScreenAnimal(int x, int duration);
    // 开启动画
    void startAnimal();


private:
    QLabel* textLabel;              // 弹幕中的文本
    QLabel* imageLabel; // 弹幕中⽤⼾头像
    QPropertyAnimation* animal; // 动画对象实例指针
};


class BulletScreenInfo
{
public:
    QString userId; // 发送弹幕⽤⼾
    QString videoId; // 弹幕对应的视频Id
    int64_t playTime; // 发送弹幕时当前播放时间
    QString text; // 弹幕内容
    BulletScreenInfo(const QString& userId = "", int64_t playTime = 0,
                     const QString& text = "")
        : userId(userId)
        , playTime(playTime)
        , text(text)
    {}

};

#endif // BULLETSCREENITEM_H
