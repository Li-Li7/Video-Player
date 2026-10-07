#ifndef PLAYERPAGE_H
#define PLAYERPAGE_H

#include <QWidget>
#include "volume.h"
#include "playspeed.h"
#include "login.h"
#include "mpv/mpvplayer.h"
#include <QFrame>
#include "bulletscreenitem.h"
#include <QMap>
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
    // 加载视频
    void startPlaying(const QString &videoFilePath);
    void onPlayPositionChanged(int64_t playTime); // 播放位置改变
    void setPlayProgress(double playRatio); // 设置播放进度
    void onBulletScreenClicked(); // 弹幕开关控制
    void onsendBulletScreenBtnClicked(const QString &text); // 发送弹幕



    // 加载弹幕数据
    void loadBulletScreenData();

private slots:
    void onSpeedBtnClicked(); // 倍速播放
    void onLkeImageBtnClcked(); // 点赞
    void onPlayBtnClicked();
    void onPlaySpeedChanged(double speed); // 倍数播放
    void setVolume(int volumeRatio); // ⾳量调节
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    // 将秒转换为：xx:xx:xx 格式时间
    QString secondToTime(int64_t second);
    // 弹幕区域布局
    void initBarrageArea();
    // 显⽰弹幕
    void showBulletScree();



private:
    Ui::PlayerPage *ui;
    QPoint dragPos;
    bool isDragging=false;
    bool isGlobalMode=true;//是否是全局模式
    int64_t playTime = 0; // 当前播放时⻓
    MpvPlayer* mpvPlayer = nullptr; // 封装mpv库，控制播放视频
    bool isPlay=false;//默认情况下，暂停，不播放

    Volume* volume;
    PlaySpeed* playSpeed;
    Login* login;

    QTimer* hideTimer = nullptr;

    QString videoFilePath;     // 新增：记录当前视频路径，重播要用
    int64_t duration = 0;      // 新增：真实总时长
    bool    isEnded  = false;  // 新增：是否已播完

    // 弹幕相关信息
    QDialog* barrageArea;
    QFrame* top;
    QFrame* middle;
    QFrame* bottom;
    QMap<int64_t, QList<BulletScreenInfo>> bulletScreenLists;   //临时保存弹幕信息
    bool isStartBS = true; // 是否开启弹幕，默认弹幕开启


};

#endif // PLAYERPAGE_H
