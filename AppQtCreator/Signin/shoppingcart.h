#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include "mydb.h"
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QtSql/QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSpinBox>
#include "thanh_toan.h"
#define Path_to_DB "E:/Zalo/ShoppingCartUpdata/DataShop.db"
QT_BEGIN_NAMESPACE
namespace Ui {
class ShoppingCart;
}
QT_END_NAMESPACE

class ShoppingCart : public QMainWindow
{
    Q_OBJECT

public:
    ShoppingCart(QWidget *parent = nullptr);
    ~ShoppingCart();
signals:
    // Tín hiệu để thông báo khi cần chuyển đổi sang cửa sổ đăng nhập
    void returnShoppingDisplay();
private slots:
    void on_checkBtn_clicked();

    void on_checkOutBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::ShoppingCart *ui;
    QSqlDatabase DBConnection;
    thanh_toan *thanhToan;

};
#endif // SHOPPINGCART_H
