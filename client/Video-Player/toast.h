#ifndef TOAST_H
#define TOAST_H

#include <QDialog>

class Toast:public QDialog
{
    Q_OBJECT
public:
    Toast();

    // 此处不需要指定⽗窗⼝. Toast⼀般是在整个桌⾯上显⽰的
    Toast(const QString& text, QWidget *pWidget);
    Toast(const QString& text);
    // 并不需要⼿动来 new 这个对象, ⽽是通过 showMessage 来弹出窗⼝
    static void showMessage(const QString& text);
    static void showMessage(const QString& text, QWidget *pWidget);
private:
    void initUI(const QString& text);

};

#endif // TOAST_H
