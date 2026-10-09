#include "videoplayerserver.h"
#include "ui_videoplayerserver.h"

VideoPlayerServer::VideoPlayerServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VideoPlayerServer)
{
    ui->setupUi(this);
}

VideoPlayerServer::~VideoPlayerServer()
{
    delete ui;
}
