#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include "util.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class VideoPlayer;
}
QT_END_NAMESPACE

enum StackedWidgetPage{
    HomePage=0,
    MyselfPage=1,
    AdminPage=2,
    UploadPage=3
};

class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer() override;
    static VideoPlayer* getInstance();

private slots:
    void onSwitchPage(int pageId);

private:
    VedioPlayer(QWidget *parent = nullptr);

    //设置界面的UI部分
    void initUI();
    //绑定槽函数
    void connectSigalAndSlot();

    // 重置页面切换按钮
    void resetswitchBtnInfo(int pageId);
    //鼠标按下事件,移动事件

    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    // void leaveEvent(QEvent *event)override;


private:
    Ui::VideoPlayer *ui;
    static VideoPlayer* instance;
    // QPoint dragPos;
    bool isGlobalMode=true;//是否是全局模式
    QPoint m_dragPos;
    bool m_isDragging = false;


};
#endif // VIDEOPLAYER_H
