#ifndef THANH_TOAN_H
#define THANH_TOAN_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QString>
#include "mydb.h"
#include "help_shippingadd.h"
#include "help_method.h"
#include "help_gift.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class thanh_toan;
}
QT_END_NAMESPACE

class thanh_toan : public QMainWindow
{
    Q_OBJECT

public:
    thanh_toan(QWidget *parent = nullptr);
    ~thanh_toan();

private slots:
//    void on_btn_submit_clicked();

 //   void on_btn_apply_clicked();

    void on_btn_question_clicked();

    void on_btn_question_2_clicked();

    void on_btn_question_3_clicked();

   void on_btn_checkPrice_clicked();

    void on_cb_method_currentTextChanged(const QString &arg1);

    void on_btn_confim_clicked();

    void on_pushButton_clicked();
signals:
    // Tín hiệu để thông báo khi cần chuyển đổi sang cửa sổ đăng nhập
    void returnShoppingCart();
private:
    Ui::thanh_toan *ui;
    QSqlDatabase db;
    help_shippingAdd *help;
    help_method *help_2;
    help_gift *help_3;

};
#endif // THANH_TOAN_H
