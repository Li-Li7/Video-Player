#ifndef VIDEOPLAYERSERVER_H
#define VIDEOPLAYERSERVER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class VideoPlayerServer;
}
QT_END_NAMESPACE

class VideoPlayerServer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayerServer(QWidget *parent = nullptr);
    ~VideoPlayerServer() override;

private:
    Ui::VideoPlayerServer *ui;
};
#endif // VIDEOPLAYERSERVER_H
