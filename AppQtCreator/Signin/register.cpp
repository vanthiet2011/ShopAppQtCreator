#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

}

Register::~Register()
{
    delete ui;
}


void Register::resetElements()
{
    ui->line_firstName->clear();
    ui->line_lastName->clear();
    ui->line_userName->clear();
    ui->line_password->clear();
    ui->line_confirmPassword->clear();
}
void Register::on_btn_close_window_clicked()
{
    close();
}


void Register::on_btn_minimize_window_clicked()
{
    showMinimized();
}


void Register::on_btn_sw_login__clicked()
{
    close();
    emit switchToLogin();
}


void Register::on_btn_hidden_pw_clicked()
{
    if(ui->line_password->echoMode()==QLineEdit::Password){
        ui->line_password->setEchoMode(QLineEdit::Normal);
        ui->btn_hidden_pw->setIcon(QIcon(":/Image/show.png"));
    }else{
        ui->line_password->setEchoMode(QLineEdit::Password);
        ui->btn_hidden_pw->setIcon(QIcon(":/Image/hidden.png"));
    }
}


void Register::on_btn_hidden_confirm_pw_clicked()
{
    if(ui->line_confirmPassword->echoMode()==QLineEdit::Password){
        ui->line_confirmPassword->setEchoMode(QLineEdit::Normal);
        ui->btn_hidden_confirm_pw->setIcon(QIcon(":/Image/show.png"));
    }else{
        ui->line_confirmPassword->setEchoMode(QLineEdit::Password);
        ui->btn_hidden_confirm_pw->setIcon(QIcon(":/Image/hidden.png"));
    }
}


void Register::on_btn_signup_clicked()
{
    QDate currentDate = QDate::currentDate();
    QString registerDate = currentDate.toString("yyyy-MM-dd");
    QString firstName = ui->line_firstName->text();
    QString lastName = ui->line_lastName->text();
    QString userName = ui->line_userName->text();
    QString telephone = ui->line_telephone->text();
    QString passWord = ui->line_password->text();
    QString confirm_PassWord = ui->line_confirmPassword->text();

    if(firstName.isEmpty() || lastName.isEmpty() || userName.isEmpty() || passWord.isEmpty() || confirm_PassWord.isEmpty() || telephone.isEmpty()){
        ui->lb_notice->setText("Input Error: All fields must be filled out");
        return;
    }

    // Kiểm tra mật khẩu nhập lại
    if(passWord != confirm_PassWord){
        ui->lb_notice->setText("Your confirm Password is incorrect");
        return;
    }

    // Gọi phương thức registerUser từ class User để kiểm tra và đăng ký người dùng
    User user;
    bool registrationStatus = user.registerUser(userName, passWord, registerDate, firstName, lastName, telephone);

    if (registrationStatus) {
        resetElements();
        ui->lb_notice->setText("Registration Successful");
    } else {
        ui->lb_notice->setText("Registration Error: The username is already taken.");
    }

}

