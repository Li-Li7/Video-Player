#ifndef ROLETABLE_H
#define ROLETABLE_H

#include <QWidget>
#include "paginator.h"

namespace Ui {
class RoleTable;
}

class RoleTable : public QWidget
{
    Q_OBJECT

public:
    explicit RoleTable(QWidget *parent = nullptr);
    ~RoleTable();

    // 重置按钮点击
    void onResetBtnClicked();
    // 查询按钮点击
    void onQueryBtnClicked();


private:
    //  初始化样式表
    void initStyleSheet();

private slots:
    // 将RoleTableItem添加到表格
    void updateRoleTable();
    // 新增按钮点击
    void onInsertBtnClicked();


private:
    Ui::RoleTable *ui;
    // Paginator* paginator;
    Paginator* paginator = nullptr; // 分⻚器指针
    // 保存按钮样式
    QMap<QString, QString> styleSheet;
};

#endif // ROLETABLE_H
