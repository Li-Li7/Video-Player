#ifndef CHECKTABLE_H
#define CHECKTABLE_H

#include <QWidget>
#include "checktableitem.h"
#include "paginator.h"

namespace Ui {
class CheckTable;
}

class CheckTable : public QWidget
{
    Q_OBJECT

public:
    explicit CheckTable(QWidget *parent = nullptr);
    ~CheckTable();

    // 更新审核⻚⾯table
    void updateCheckTable();
    // 重置按钮点击槽函数
    void onResetBtnClicked();
    // 查询按钮点击槽函数
    void onQueryBtnClicked();


private:
    Ui::CheckTable *ui;
    Paginator* paginator = nullptr; // 分⻚器指针
};

#endif // CHECKTABLE_H
