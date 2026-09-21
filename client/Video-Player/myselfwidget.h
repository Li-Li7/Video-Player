#ifndef MYSELFWIDGET_H
#define MYSELFWIDGET_H

#include <QWidget>

namespace Ui {
class MyselfWidget;
}

class MyselfWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyselfWidget(QWidget *parent = nullptr);
    ~MyselfWidget();
private:
    void initUI();
    // 点击上传头像按钮
    void uploadAvatarBtnClicked();
    void settingBtnClicked();
    void uploadViewBtnClicked();
private slots:
    void onAvatarBtnClicked();
    void onSettingBtnClicked();
    void onUploadVideoBtnClicked();
    void onNicknameBtnClicked();
    void onQuitBtnClicked();
signals:
    // 切换到上传视频⻚⾯
    void switchUploadVideoPage(int pageIndex);

private:
    Ui::MyselfWidget *ui;
};

#endif // MYSELFWIDGET_H
