#ifndef PLAYSLIDER_H
#define PLAYSLIDER_H

#include <QWidget>

namespace Ui {
class PlaySlider;
}

class PlaySlider : public QWidget
{
    Q_OBJECT

public:
    explicit PlaySlider(QWidget *parent = nullptr);
    ~PlaySlider();

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    void moveSlider(); // 改变outLine的geometry
signals:
    void setPlayProgress(double playRatio);
private:
    Ui::PlaySlider *ui;
    int playGrogress; // 记录当前播放⻓度
};

#endif // PLAYSLIDER_H
