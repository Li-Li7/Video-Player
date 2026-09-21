#ifndef VOLUME_H
#define VOLUME_H

#include <QWidget>
#include "util.h"

namespace Ui {
class Volume;
}

class Volume : public QWidget
{
    Q_OBJECT

public:
    explicit Volume(QWidget *parent = nullptr);
    ~Volume();
    int getVolume()const;
private:
    bool eventFilter(QObject *watched, QEvent *event);
    void calcVolume();
signals:
    void setVolume(int volume);
private:
    Ui::Volume *ui;
    int volume=30;
};

#endif // VOLUME_H
