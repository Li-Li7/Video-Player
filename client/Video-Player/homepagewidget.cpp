#include "homepagewidget.h"
#include "ui_homepagewidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "videobox.h"
HomePageWidget::HomePageWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomePageWidget)
{
    ui->setupUi(this);
    initKindsAndTags();
    initRefreshAndTopBtn();
    initVideos();
}

HomePageWidget::~HomePageWidget()
{
    delete ui;
}
// ============================================================================
void HomePageWidget::initKindsAndTags()
{
    // 分类和该分类下所有标签的映射（存到成员，否则函数结束就没了）
    kindToTags = {
        {"历史", {"中国史", "世界史", "历史⼈物", "艺术", "⽂化", "奇闻"}},
        {"美⻝", {"美⻝测评", "美⻝制作", "美⻝攻略", "美⻝记录", "探店", "⽔果", "海鲜"}},
        {"游戏", {"游戏攻略", "单机游戏", "电⼦竞技", "⼿机游戏", "⽹络游戏", "游戏赛事","桌游棋牌"}},
        {"科技", {"数码", "软件应⽤", "智能家居", "⼿机", "电脑", "⼈⼯智能", "基础设施"}},
        {"运动", {"篮球", "⾜球", "乒乓球", "⽻⽑球", "健⾝", "竞技体育", "运动装备"}},
        {"动物", {"喵星⼈", "汪星⼈", "宠物知识", "动物资讯", "野⽣动物", "动物世界", "萌宠"}},
        {"旅⾏", {"旅游攻略", "旅⾏Vlog", "⾃驾游", "交通", "环球旅⾏", "露营", "野外⽣存"}},
        {"电影", {"电影解说", "电影推荐", "电影剪辑", "搞笑", "吐槽", "悬疑", "经典"}}};

    // QHash 遍历顺序不确定，用 QList 保证界面上分类顺序固定
    const QList<QString> kinds = {"历史", "美⻝", "游戏", "科技", "运动", "动物", "旅⾏", "电影"};

    // 文本为"分类"的按钮
    QPushButton *kindBtn = buildSelectBtn(ui->classifys, "#3ECEFF", "分类");
    kindBtn->setObjectName("kindBtn");
    ui->classifyHLayout->addWidget(kindBtn);
    connect(kindBtn, &QPushButton::clicked, this, &HomePageWidget::onKindsBtnClicked);

    // 具体的分类按钮
    for(const auto& kind : kinds)
    {
        QPushButton* kindItemBtn = buildSelectBtn(ui->classifys, "#222222", kind);
        ui->classifyHLayout->addWidget(kindItemBtn);

        // 给分类按钮绑定槽函数：clicked 带 bool 参数，不能直接连带 QPushButton* 的槽，用 lambda 转接
        connect(kindItemBtn, &QPushButton::clicked, this, [this, kindItemBtn]{
            onKindBtnClicked(kindItemBtn);
        });
    }
    ui->classifyHLayout->setSpacing(8);
}

QPushButton* HomePageWidget::buildSelectBtn(QWidget *parent, const QString &color, const QString &text)
{
    QPushButton* btn = new QPushButton(text, parent);
    btn->setStyleSheet("color : " + color);
    btn->setMinimumHeight(26);
    // 18:文本到按钮边界的距离
    btn->setFixedWidth(text.size()*16+18+18);
    return btn;
}

void HomePageWidget::resetTags(const QList<QString> &tags)
{
    // //创建标签的说明
    // QPushButton* tag=buildSelectBtn(ui->labels,"#666666","标签");
    // ui->labelHLayout->addWidget(tag);

    // 创建标签的说明
    QPushButton* tag = buildSelectBtn(ui->labels, "#3ECEFF", "标签");
    tag->setObjectName("tagBtn");
    ui->labelHLayout->addWidget(tag);
    connect(tag, &QPushButton::clicked, this, &HomePageWidget::onTagsBtnClicked);
    //创建每个具体标签
    for(auto &tagText:tags)
    {
        QPushButton* tagItem=buildSelectBtn(ui->labels,"#666666",tagText);
        ui->labelHLayout->addWidget(tagItem);
        connect(tagItem,&QPushButton::clicked,this,[=](){
            onTagBtnClicked(tagItem);
        });
    }
    ui->labelHLayout->setSpacing(4);
}

void HomePageWidget::initRefreshAndTopBtn()
{

    refreshTopWidget=new QWidget(this);
    refreshTopWidget->setFixedSize(42,94);
    refreshTopWidget->setStyleSheet("QPushButton{"
                                    "border-radius : 21px;"
                                    "border : none;"
                                    "background-color : rgba(221, 221, 221, 0.4);}"
                                    "QPushButton:hover{background-color : rgba(102, 102, 102, 0.4);}");
    QVBoxLayout* layout=new QVBoxLayout(refreshTopWidget);


    //按钮
    QPushButton* topBtn=new QPushButton(refreshTopWidget);
    topBtn->setFixedSize(42,42);
    topBtn->setStyleSheet("border-image:url(:/images/homePage/zhiding.png);");
    layout->addWidget(topBtn);

    QPushButton* refreshBtn=new QPushButton(refreshTopWidget);
    refreshBtn->setFixedSize(42,42);
    refreshBtn->setStyleSheet("border-image : url(:/images/homePage/shuaxin.png);");
    layout->addWidget(refreshBtn);

    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(10);

    connect(topBtn,&QPushButton::clicked,this,&HomePageWidget::onTopBtnClicked);
    connect(refreshBtn,&QPushButton::clicked,this,&HomePageWidget::onRefreshBtnClicked);


}

void HomePageWidget::initVideos()
{
    for(int i=0;i<16;++i)
    {
        VideoBox* video=new VideoBox();
        ui->videoGLayout->addWidget(video, i/4, i%4);
    }
}

void HomePageWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (refreshTopWidget)
    {
        const int margin = 20;  // 距右下角的边距，想调就改这个数
        refreshTopWidget->move(
            width()  - 42 - margin,
            height() - 94 - margin
            );
    }
}


void HomePageWidget::onKindBtnClicked(QPushButton *clickedKindBtn)
{
    // 如果相同分类按钮连续点击，将不再重新获取
    const QString kindText = clickedKindBtn->text();
    if(curKind == kindText)
    {
        return;
    }
    curKind = kindText;
    curTag = "";

    // 设置当前被点击分类按钮的高亮显示
    clickedKindBtn->setStyleSheet("background-color : #F1FDFF;"
                                  "color : #3ECEFF;");
    // 清除之前点击过的分类按钮上的高亮显示
    // 获取所有的分类按钮--即获取classifys中所有类型为QPushButton*的孩子.因为所有分类按钮的父元素都是ui->classifys
    QList<QPushButton*> kindBtns = ui->classifys->findChildren<QPushButton*>();
    for(auto& kindBtn : kindBtns){
        if(kindBtn != clickedKindBtn){
            kindBtn->setStyleSheet("color : #222222;");
        }
    }

    // 先删除分类布局器中的之前分类按钮下中的所有标签
    QList<QPushButton*> tagBtns = ui->labels->findChildren<QPushButton*>();
    for(auto& tagBtn : tagBtns){
        ui->labelHLayout->removeWidget(tagBtn);
        delete tagBtn;
    }

    resetTags(kindToTags.value(kindText));

}

void HomePageWidget::onTagBtnClicked(QPushButton *clickedTagBtn)
{
    // 防止相同的标签按钮重复点击
    QString tagText = clickedTagBtn->text();
    if(curTag == tagText){
        return;
    }

    curTag = tagText;

    // 将被点击的标签按钮设置为高亮显示
    clickedTagBtn->setStyleSheet("background-color : #F1FDFF;"
                                 "color : #3ECEFF;");

    // 获取当前分类下的所有标签，并清除之前点击过的标签上的高亮显示
    QList<QPushButton*> tagBtns = ui->labels->findChildren<QPushButton*>();
    for(auto& tagBtn : tagBtns)
    {
        if(tagBtn != clickedTagBtn){
            tagBtn->setStyleSheet("color : #666666;");
        }
    }
}

void HomePageWidget::onKindsBtnClicked()
{
    // 只展示分类按钮不展示标签按钮，将所有标签按钮删除掉
    QList<QPushButton*> tagBtns = ui->labels->findChildren<QPushButton*>();
    for(auto& tagBtn : tagBtns)
    {
        ui->labelHLayout->removeWidget(tagBtn);
        delete tagBtn;
    }

    // 将所有分类按钮样式设置为未点击样式
    QList<QPushButton*> kindBtns = ui->classifys->findChildren<QPushButton*>();
    for(auto& kindBtn : kindBtns){
        kindBtn->setStyleSheet("color : #222222;");
    }
    // 让文本为分类的按钮高亮
    QPushButton* kind = ui->classifys->findChild<QPushButton*>("kindBtn");
    kind->setStyleSheet("background-color : #F1FDFF;"
                        "color : #3ECEFF;");

}

void HomePageWidget::onTagsBtnClicked()
{
    // 重置所有标签按钮的样式，选中文本为标签的按钮
    QList<QPushButton*> tagBtns = ui->labels->findChildren<QPushButton*>();
    for(auto& tagBtn : tagBtns){
        tagBtn->setStyleSheet("color : #666666;");
    }
    QPushButton* tag = ui->labels->findChild<QPushButton*>("tagBtn");
    tag->setStyleSheet("background-color : #F1FDFF;"
                       "color : #3ECEFF;");
    // ===== 修复版补充（已注释，未删除）=====
    // 还没点过分类时标签按钮不存在，直接解引用会崩溃，应判空：
    if(tag){ tag->setStyleSheet("background-color : #F1FDFF;color : #3ECEFF;"); }
    curTag = "";
}

void HomePageWidget::onTopBtnClicked()
{

}

void HomePageWidget::onRefreshBtnClicked()
{

}

// ============================================================================
// 下面是完整修复版代码（已按要求注释保留，未删除）
// 修复点汇总：
//   1. 构造函数调用 initKindsAndTag() 与头文件声明 initKindsAndTags() 差一个 s -> 编译失败
//   2. resetTags() 全项目无调用点 -> 标签永远不显示
//   3. tags 是局部 QHash，函数结束即销毁 -> 改为成员 kindToTags
//   4. 分类按钮 clicked 只连了改背景色的 lambda，没连 onKindBtnClicked
//   5. buildSelectBtn(ui->labels,"#66666",...) 颜色值只有 5 位，非法 -> #666666
//   6. "分类"总按钮未连接 onKindsBtnClicked；findChild 未判空
// 若要启用：取消下面注释，并把上面对应的原始函数删掉/注释，同时恢复头文件中被注释的成员。

//
// void HomePageWidget::clearTags()
// {
//     const QList<QPushButton*> tagBtns = ui->labels->findChildren<QPushButton*>();
//     for(QPushButton* tagBtn : tagBtns)
//     {
//         ui->labelHLayout->removeWidget(tagBtn);
//         delete tagBtn;
//     }
// }
//
// void HomePageWidget::resetTags(const QList<QString> &tags)
// {
//     // 先把上一批标签清掉，否则会越点越多、层层叠加
//     clearTags();
//
//     // 创建标签的说明
//     QPushButton* tag = buildSelectBtn(ui->labels, "#3ECEFF", "标签");
//     tag->setObjectName("tagBtn");
//     ui->labelHLayout->addWidget(tag);
//     connect(tag, &QPushButton::clicked, this, &HomePageWidget::onTagsBtnClicked);
//     //创建每个具体标签
//     for(const auto &tagText : tags)
//     {
//         // 注意：颜色值必须是 6 位，#66666 是非法颜色，Qt 会解析失败
//         QPushButton* tagItem = buildSelectBtn(ui->labels, "#666666", tagText);
//         ui->labelHLayout->addWidget(tagItem);
//         connect(tagItem, &QPushButton::clicked, this, [this, tagItem](){
//             onTagBtnClicked(tagItem);
//         });
//     }
//     ui->labelHLayout->setSpacing(4);
// }
