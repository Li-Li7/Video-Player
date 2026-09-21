#ifndef PAGEBUTTON_H
#define PAGEBUTTON_H

#include <QPushButton>

class PageButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PageButton(int page, QWidget* parent = nullptr);
    void setActive(bool active);
    void setFolded(bool folded);
    void setPage(int page);
    int getPage() const;
    // 检测按钮是否处于点击选中状态
    bool isActived() const;
    // 检测按钮是否为折叠按钮
    bool isFolded() const;

private:
    int page; // 按钮上⻚号
    // 按钮是否点击选中，默认未点击选中
    bool isActiveBtn = false;
    // 是否为折叠按钮
    bool isFoldedBtn = false;

};

#endif // PAGEBUTTON_H
