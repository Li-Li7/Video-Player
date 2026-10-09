#include "videoplayerserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoPlayerServer w;
    w.show();
    return QApplication::exec();
}
