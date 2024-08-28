#ifndef REGISTER_H
#define REGISTER_H
#include "mydb.h"
#include <QMainWindow>
#include <QtCore>
#include <QtSql>
#include "User.h"
namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
signals:
    // Tín hiệu để thông báo khi cần chuyển đổi sang cửa sổ đăng nhập
    void switchToLogin();
private slots:
    void on_btn_close_window_clicked();

    void on_btn_minimize_window_clicked();

    void on_btn_sw_login__clicked();

    void on_btn_hidden_pw_clicked();

    void on_btn_hidden_confirm_pw_clicked();

    void on_btn_signup_clicked();

private:
    Ui::Register *ui;
    void resetElements();
};

#endif // REGISTER_H
