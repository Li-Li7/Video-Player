#ifndef DATACENTER_H
#define DATACENTER_H

#include <QObject>

class DataCenter : public QObject
{
    Q_OBJECT
public:
    explicit DataCenter(QObject *parent = nullptr);

signals:
};

#endif // DATACENTER_H
