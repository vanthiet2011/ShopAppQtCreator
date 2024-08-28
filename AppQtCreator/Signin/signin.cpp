#include "signin.h"
#include "./ui_signin.h"


#include "Global.h"


Signin::Signin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Signin)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

}

Signin::~Signin()
{
    delete ui;

}

void Signin::on_btn_hidden_pw_clicked()
{
    if(ui->line_password->echoMode()==QLineEdit::Password){
        ui->btn_hidden_pw->setIcon(QIcon(":/Image/show.png"));
        ui->line_password->setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->btn_hidden_pw->setIcon(QIcon(":/Image/hidden.png"));
        ui->line_password->setEchoMode(QLineEdit::Password);
    }
}


void Signin::on_btn_close_window_clicked()
{
    close();
}


void Signin::on_btn_minimize_window_clicked()
{
    showMinimized();
}


void Signin::on_btn_register_clicked()
{
    hide();
    register_customer = new Register(this);
    register_customer->show();
    connect(register_customer, &Register::switchToLogin, this, &Signin::show);
}


void Signin::on_cb_admin_toggled(bool checked)
{

}

void Signin::on_cb_admin_stateChanged(int arg1)
{
    if(ui->cb_admin->isChecked()==1){
        ui->line_userName->setPlaceholderText("Administrator");
    }else{
        ui->line_userName->setPlaceholderText("Username");
    }
}

int getCartId(){
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.prepare("SELECT *FROM Cart WHERE userId ='"+USER_ID+"'");
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        return -1;
    }else {
        if(query.next() == 1)
        {
            qDebug() <<"read was successful "<< query.lastQuery();

            int cartId = query.value(0).toInt();
            return cartId;
        }
    }
}

void Signin::on_btn_login_now_clicked()
{
    user = new User(this);
    QString Username = ui->line_userName->text();
    QString Password = ui->line_password->text();
    bool isAdmin = ui->cb_admin->isChecked();
    if(Username.isEmpty() || Password.isEmpty()){
        ui->lb_notice->setText("Input Error All fields must be filled out");
        return;
    }
    if (user->loginUser(Username, Password, isAdmin)) {
        ui->lb_notice->setText("Login success");
        // Handle login success
        resetElements();
        if(isAdmin){
            hide();
            shop_display = new Shop_display();
            shop_display->show();
            connect(shop_display, &Shop_display::returnToLogin, this, &Signin::show);
        }else{
            hide();
            Shop_display_admin = new shop_display_admin();
            Shop_display_admin->show();
            connect(Shop_display_admin, &shop_display_admin::returnToLogin, this, &Signin::show);
            CART_ID = getCartId();
            qDebug() << "CART ID LOGIN"<<CART_ID;
        }
    }else{
        ui->lb_notice->setText("Failed to login");
        // Handle login failure
    }
}
void Signin::resetElements()
{
    ui->line_userName->clear();
    ui->line_password->clear();
}
