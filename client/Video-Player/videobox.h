#ifndef VIDEOBOX_H
#define VIDEOBOX_H

#include <QWidget>
#include "playerpage.h"
namespace Ui {
class VideoBox;
}

class VideoBox : public QWidget
{
    Q_OBJECT

public:
    explicit VideoBox(QWidget *parent = nullptr);
    ~VideoBox();

    bool eventFilter(QObject *watched,QEvent* event)override;
private:
    void onPlayBtnClicked();

private:
    Ui::VideoBox *ui;
    PlayerPage* playerPage = nullptr;
    // model::VideoInfo videoInfo;
    QPixmap videoCoverImage;   // 视频封面画图
    QPixmap userAvatar;        // 用户头像
};

#endif // VIDEOBOX_H
