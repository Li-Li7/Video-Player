#ifndef HOMEPAGEWIDGET_H
#define HOMEPAGEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHash>
#include <QList>
#include <QString>

namespace Ui {
class HomePageWidget;
}

// 向服务器获取视频列表的方式
enum VideoListStyle
{
    AllStyle,        // 所有视频类型
    KindStyle,       // 分类视频列表
    TagStyle,        // 标签视频列表
    SearchStyle      // 搜索视频列表
};

class HomePageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomePageWidget(QWidget *parent = nullptr);
    ~HomePageWidget();
private:
    void initKindsAndTags();
    QPushButton* buildSelectBtn(QWidget* parent,const QString &color,const QString &text);
    void resetTags(const QList<QString> &tags);
    void initRefreshAndTopBtn();
    void initVideos();

    // ===== 修复版新增（已注释，未删除）=====
    // 清空标签行中所有按钮
    // void clearTags();
protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    // 分类按钮点击
    void onKindBtnClicked(QPushButton* clickedKindBtn);

    // 标签按钮点击
    void onTagBtnClicked(QPushButton* clickedTagBtn);

    // 文本为分类的按钮点击
    void onKindsBtnClicked();

    // 文本为标签的按钮点击
    void onTagsBtnClicked();

    //置顶按钮
    void onTopBtnClicked();

    //刷新按钮点击
    void onRefreshBtnClicked();
private:
    Ui::HomePageWidget *ui;
    QString curKind;       // 保存当前获取哪个分类下的视频
    QString curTag;        // 保存当前获取哪个标签下的视频
    // 分类 -> 该分类下所有标签。必须是成员，放局部变量的话函数结束就销毁了
    QHash<QString, QList<QString>> kindToTags;
    QWidget* refreshTopWidget = nullptr;
};

#endif // HOMEPAGEWIDGET_H
