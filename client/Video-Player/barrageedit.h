#ifndef BARRAGEEDIT_H
#define BARRAGEEDIT_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class BarrageEdit:public QLineEdit
{
    Q_OBJECT
public:
    BarrageEdit();
    explicit BarrageEdit(QWidget *parent = nullptr);
    // 鼠标在编辑框中点击时
    // virtual void mousePressEvent(QMouseEvent* event)override;

private slots:
    // void onSendBSBtnClicked();

signals:
    void sendBulletScreen(const QString& text);
private:
     QPushButton* sendBSBtn;
};

#endif // BARRAGEEDIT_H
