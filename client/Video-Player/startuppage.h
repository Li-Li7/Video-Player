#ifndef STARTUPPAGE_H
#define STARTUPPAGE_H

#include <QDialog>

class StartUpPage : public QDialog
{
    Q_OBJECT
public:
    explicit StartUpPage(QDialog *parent = nullptr);

    //开启定时器
    void startTimer();
signals:
private:
    bool loginSuccess=true;
    bool myselfInfoSuccess=true;
};

#endif // STARTUPPAGE_H
