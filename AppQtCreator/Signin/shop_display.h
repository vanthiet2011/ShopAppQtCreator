#ifndef SHOP_DISPLAY_H
#define SHOP_DISPLAY_H

#include <QMainWindow>
#include <QtCore>
#include <QtSql>

#include "addproduct.h"
#include "detailproduct.h"


#include "mydb.h"

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
#include "Global.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Shop_display;
}
QT_END_NAMESPACE

class Shop_display : public QMainWindow
{
    Q_OBJECT

public:
    Shop_display(QWidget *parent = nullptr);
    ~Shop_display();

private slots:

    void on_Button_Add_Data_clicked();

    void on_pushButton_Display_From_Database_clicked();

    void on_on_btn_show_Jacket_clicked();

    void on_on_btn_show_Tshirt_clicked();

    void on_on_btn_show_Polo_clicked();

    void on_on_btn_show_Pant_clicked();

    void on_on_btn_show_Short_clicked();

    void on_on_pushButton_Search_clicked();

    void on_on_pushButton_Menu_clicked();





    void on_pushButton_3_clicked();
signals:
    // Tín hiệu để thông báo khi cần chuyển đổi sang cửa sổ đăng nhập
    void returnToLogin();
private:
    Ui::Shop_display *ui;
    // Add_Data_products *ptrAddDataProducts;
    AddProduct *ptrAddProduct;
    DetailProduct *ptrDetailProduct;



    QPropertyAnimation *animation_1;
    QPropertyAnimation *animation_2;

};
#endif // SHOP_DISPLAY_H
