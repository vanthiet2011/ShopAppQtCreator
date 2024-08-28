#ifndef SIGNIN_H
#define SIGNIN_H
#include "mydb.h"
#include <QMainWindow>
#include <QtCore>
#include <QtSql>
#include "register.h"
#include "shop_display.h"
#include "shop_display_admin.h"
#include "User.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Signin;
}
QT_END_NAMESPACE

class Signin : public QMainWindow
{
    Q_OBJECT

public:
    Signin(QWidget *parent = nullptr);
    ~Signin();
    bool adminMode=false;

private slots:
    void on_btn_hidden_pw_clicked();

    void on_btn_close_window_clicked();

    void on_btn_minimize_window_clicked();

    void on_btn_register_clicked();

    void on_cb_admin_toggled(bool checked);

    void on_cb_admin_stateChanged(int arg1);

    void on_btn_login_now_clicked();

private:
    void resetElements();
    Ui::Signin *ui;
    Register *register_customer;
    Shop_display* shop_display;
    shop_display_admin* Shop_display_admin;
    User *user;
};
#endif // SIGNIN_H
