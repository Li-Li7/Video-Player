#ifndef PLAYERPAGE_H
#define PLAYERPAGE_H

#include <QWidget>
#include "volume.h"
#include "playspeed.h"
#include "login.h"

namespace Ui {
class PlayerPage;
}

class PlayerPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerPage(QWidget *parent = nullptr);
    ~PlayerPage();

    void mousePressEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    // 移动窗⼝控件
    void moveWindows(const QPoint& point);

private slots:
    void onVolumeBtnClicked(); // ⾳量调节
    void onSpeedBtnClicked(); // 倍速播放
    void onLkeImageBtnClcked(); // 点赞


private:
private:
    Ui::PlayerPage *ui;
    QPoint dragPos;
    bool isDragging=false;
    bool isGlobalMode=true;//是否是全局模式
    Volume* volume;
    PlaySpeed* playSpeed;
    Login* login;
};

#endif // PLAYERPAGE_H
