#ifndef SHOP_DISPLAY_ADMIN_H
#define SHOP_DISPLAY_ADMIN_H

#include <QMainWindow>
#include <QtCore>
#include <QtSql>

#include "addproduct.h"
#include "detailproduct.h"
#include "mydb.h"
#include "shoppingcart.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPixmap>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QBuffer>
#include <QByteArray>
#include <QTableWidgetItem>

#include <QPropertyAnimation>





namespace Ui {
class shop_display_admin;
}

class shop_display_admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit shop_display_admin(QWidget *parent = nullptr);
    ~shop_display_admin();

private slots:
    void on_pushButton_Display_From_Database_clicked();

    void on_on_btn_show_Tshirt_clicked();

    void on_on_btn_show_Jacket_clicked();

    void on_on_btn_show_Polo_clicked();

    void on_on_btn_show_Pant_clicked();

    void on_on_btn_show_Short_clicked();

    void on_on_pushButton_Search_clicked();

    void on_on_pushButton_Menu_clicked();
    void on_pushButton_3_clicked();

 //   void on_pushButton_clicked();

    void on_btn_cart_clicked();

signals:
    // Tín hiệu để thông báo khi cần chuyển đổi sang cửa sổ đăng nhập
    void returnToLogin();
private:
    Ui::shop_display_admin *ui;
    AddProduct *ptrAddProduct;
    DetailProduct *ptrDetailProduct;
    QPropertyAnimation *animation_1;
    QPropertyAnimation *animation_2;
    ShoppingCart *shoppingCart;
};

#endif // SHOP_DISPLAY_ADMIN_H
