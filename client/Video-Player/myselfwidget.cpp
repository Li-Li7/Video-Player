#include "myselfwidget.h"
#include "ui_myselfwidget.h"

#include <QFileDialog>
#include "util.h"
#include "modifymyselfdialog.h"
#include "videobox.h"
#include "videoplayer.h"
MyselfWidget::MyselfWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyselfWidget)
{
    ui->setupUi(this);
    initUI();
}

MyselfWidget::~MyselfWidget()
{
    delete ui;
}

void MyselfWidget::initUI()
{
    //隐藏关注按钮
    ui->attentionBtn->hide();
    ui->uploadVideoBtn->setFlat(true);
    //头像按钮绑定槽函数
    connect(ui->avatarBtn, &AvatarButton::clicked, this,&MyselfWidget::uploadAvatarBtnClicked);
    //
    connect(ui->settingBtn,&QPushButton::clicked,this,&MyselfWidget::settingBtnClicked);


    for (int i = 0; i < 16; ++i)
    {
        VideoBox* box = new VideoBox(this);
        ui->layout->addWidget(box, i/4, i%4);
    }
}


void MyselfWidget::uploadAvatarBtnClicked()
{
    QString fileName=QFileDialog::getOpenFileName(nullptr, "选择头像", "","Image Files (*.jpg ,*.png)");
    if (fileName.isEmpty()) {
        LOG() << "取消选择头像";
        return;
    }
    QByteArray fileData = loadFileToByteArray(fileName);
    if (fileData.isEmpty()) {
        LOG() << "头像⽂件读取失败";
        return;
    }
    ui->avatarBtn->setIcon(makeCircleIcon(fileData, ui->avatarBtn->width()/2));
}

void MyselfWidget::settingBtnClicked()
{
    // 弹出对话框设置⽤⼾信息
    ModifyMyselfDialog* dialog = new ModifyMyselfDialog();
    dialog->exec();
    delete dialog;

}

void MyselfWidget::uploadViewBtnClicked()
{
    QString videoFilePath = QFileDialog::getOpenFileName(nullptr, "上传视频", "","Videos (*.mp4 *.rmvb *.avi *.mov)");
    if(!videoFilePath.isEmpty())
    {
        // 视频⼤⼩限制，上限为4G
        QFileInfo fileInfo(videoFilePath);
        int64_t fileSize = fileInfo.size();
        if(fileSize > 4*1024*1024)
        {
            LOG()<<"视频⽂件必须⼩于4G";
            return;
        }
        emit switchUploadVideoPage(UploadPage);
    }

}

void MyselfWidget::onAvatarBtnClicked()
{

}

void MyselfWidget::onSettingBtnClicked()
{

}

void MyselfWidget::onUploadVideoBtnClicked()
{

}

void MyselfWidget::onNicknameBtnClicked()
{

}

void MyselfWidget::onQuitBtnClicked()
{

}
