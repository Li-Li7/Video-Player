#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>

class netclient : public QObject
{
    Q_OBJECT
public:
    explicit netclient(QObject *parent = nullptr);

signals:
};

#endif // NETCLIENT_H
