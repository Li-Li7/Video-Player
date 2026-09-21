#ifndef PAGESWITCHBUTTON_H
#define PAGESWITCHBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class PageSwitchButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PageSwitchButton(QWidget *parent = nullptr);
    //设置按钮上面的图片和文字
    void setImageAndText(const QString &imagePath, const QString &text,int pageId);
    void setTextColor(const QString& textColor);
    int getPageId()const;
    void setImage(const QString& imagePath);

protected:
private:
    void mousePressEvent(QMouseEvent *event);
private:
    QLabel* btnImage; // 按钮上标签
    QLabel* btnTittle; // 按钮上⽂本
    int pageId;//页面编号
signals:
    void switchPage(int pageId);
};

#endif // PAGESWITCHBUTTON_H
