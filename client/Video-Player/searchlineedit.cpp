#include "searchlineedit.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "util.h"
SearchLineEdit::SearchLineEdit(QWidget *parent)
    : QLineEdit{parent}
{
    //设置编辑框的尺寸
    setFixedSize(320,36);
    setPlaceholderText("请搜索你感兴趣的视频");
    setTextMargins(33,0,0,0);
    setObjectName("search");
    setStyleSheet("#search{"
                  "background-color:#FFFFFF;"
                  "border-radius:18px;"
                  "border:1px solid #3ECEFE;"
                  "font-family:微软雅黑;"
                  "font-size:14px;"
                  "font-style:normal;}");

    //搜索图片
    QLabel* searchImage=new QLabel(this);
    searchImage->setFixedSize(16,16);
    searchImage->setPixmap(QPixmap(":/images/homepage/sousuo.png"));

    //搜索按钮
    QPushButton* searchBtn=new QPushButton(this);
    searchBtn->setText("搜索");
    searchBtn->setFixedSize(62,32);
    searchBtn->setStyleSheet("background-color:#3ECEFE;"
                             "border-radius:16px;"
                             "font-family:微软雅黑;"
                             "font-size:14px;"
                             "color:#FFFFFF;"
                             "font-style:normal;");

    //图片与按钮放到水平布局器中,从左到右排列子控件
    QHBoxLayout* layout=new QHBoxLayout(this);
    layout->addWidget(searchImage);
    layout->addStretch();
    layout->addWidget(searchBtn);
    layout->setContentsMargins(11,0,2,0);


    connect(searchBtn,&QPushButton::clicked,this,&SearchLineEdit::onSearchBtnClicked);
    connect(this,&QLineEdit::returnPressed,this,&SearchLineEdit::onSearchBtnClicked);
}

void SearchLineEdit::onSearchBtnClicked()
{
    LOG()<<"搜索按钮点击：";


}
