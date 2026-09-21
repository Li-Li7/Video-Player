#include "barrageedit.h"
#include <QHBoxLayout>

BarrageEdit::BarrageEdit(QWidget *parent):QLineEdit{parent}
{
    // 设置编辑框的尺寸
    this->setFixedSize(1030, 32);
    this->setPlaceholderText("这个视频在说什么...");
    this->setMaxLength(30);
    this->setTextMargins(12, 6, 0, 7);  // 左 上 右 下

    // 初始化发送按钮
    sendBSBtn = new QPushButton(this);
    sendBSBtn->setFixedSize(58, 28);
    sendBSBtn->setText("发送");
    sendBSBtn->setCursor(QCursor(Qt::ArrowCursor));
    sendBSBtn->setStyleSheet("background-color : #3ECEFE;"
                             "color : #FFFFFF;"
                             "border-radius : 4px;"
                             "font-family : 微软雅黑;"
                             "font-size : 14px;");
    sendBSBtn->move(width()-sendBSBtn->width()-2, 2);
    // connect(sendBSBtn, &QPushButton::clicked, this, &BarrageEdit::onSendBSBtnClicked);
}

// void BarrageEdit::onSendBSBtnClicked()
// {

// }
