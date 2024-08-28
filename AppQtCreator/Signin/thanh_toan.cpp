#include "thanh_toan.h"
#include "./ui_thanh_toan.h"
#include <QMessageBox>
#include "help_shippingadd.h"
#include "help_method.h"
#include "help_gift.h"
#include <QString>
#include "Global.h"
thanh_toan::thanh_toan(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::thanh_toan)
{
    ui->setupUi(this);

}

thanh_toan::~thanh_toan()
{
    delete ui;
}




void thanh_toan::on_btn_question_clicked()
{
    help = new help_shippingAdd(this);
    help->show();

}


void thanh_toan::on_btn_question_2_clicked()
{
    help_2 = new help_method(this);
    help_2->show();
}


void thanh_toan::on_btn_question_3_clicked()
{
    help_3 = new help_gift(this);
    help_3->show();
}



void thanh_toan::on_btn_checkPrice_clicked()
{

}

void thanh_toan::on_cb_method_currentTextChanged(const QString &arg1)
{
    QVariant total;
    QSqlQuery query_sum(MyDB::getInstance()->getDBInstance());
    query_sum.prepare("SELECT SUM(total) AS sum FROM Order_Items_temp");
    if (!query_sum.exec()) {
        qDebug() << "Loi truy van" << query_sum.lastError().text();
    }

    // Lưu kết quả của truy vấn vào biến
    if (query_sum.next()) {
        total = query_sum.value(0).toFloat();
        if (total.isNull()) {
            qDebug() << "Không có dữ liệu trả về từ truy vấn.";
        }
        qDebug() << "Tổng giá trị của cột total_amount:" << total;
    } else {
        qDebug() << "Không có dữ liệu trả về từ truy vấn.";
    }

    float totalValue = total.toFloat();
    ui->lb_subtotal->setText(QString::number(totalValue, 'f', 2));

    ui->cb_method->setItemData(0, QVariant::fromValue(100));
    ui->cb_method->setItemData(1, QVariant::fromValue(150));
    ui->cb_method->setItemData(2, QVariant::fromValue(200));
    QVariant data;
    if(ui->cb_method->currentIndex() == 0){
        data = ui->cb_method->itemData(0);
    } else if(ui->cb_method->currentIndex() == 1){
        data = ui->cb_method->itemData(1);
    } else if(ui->cb_method->currentIndex() == 2){
        data = ui->cb_method->itemData(2);
    }

    connect(ui->cb_method, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
        QVariant data = ui->cb_method->itemData(index); // Lấy dữ liệu từ item được chọn
        float value = data.toInt(); // Chuyển đổi QVariant sang int
        ui->lb_price->setText(QString::number(value)); // Cập nhật giá trị của label

        float Subtotal = value + total.toFloat();
        ui->lb_total->setText(QString::number(Subtotal));
    });
}


void thanh_toan::on_btn_confim_clicked()
{

    QVariant total;
    QSqlQuery query_sum(MyDB::getInstance()->getDBInstance());
    query_sum.prepare("SELECT SUM(total) AS sum FROM Order_Items_temp");
    if (!query_sum.exec()) {
        qDebug() << "Loi truy van" << query_sum.lastError().text();
    }

    // Lưu kết quả của truy vấn vào biến
    if (query_sum.next()) {
        total = query_sum.value(0).toFloat();
        if (total.isNull()) {
            qDebug() << "Không có dữ liệu trả về từ truy vấn.";
        }
        qDebug() << "Tổng giá trị của cột total_amount:" << total;
    } else {
        qDebug() << "Không có dữ liệu trả về từ truy vấn.";
    }

    QString firstname =ui->firstName->text();
    QString lastname =ui->lastName->text();
    QString streetadd =ui->streetAdd->text();
    QString Apt =ui->apt->text();
    QString City =ui->city->text();
    QString Province=ui->province->text();
    QString phonenumber=ui->phoneNumber->text();
    QString methodShipping = ui->cb_method->currentText();
    QSqlQuery Query_ShippingAdd (MyDB::getInstance()->getDBInstance());
    Query_ShippingAdd.clear();

    if(firstname.isEmpty() || lastname.isEmpty() || streetadd.isEmpty() || Apt.isEmpty() || City.isEmpty() || Province.isEmpty()|| phonenumber.isEmpty() || methodShipping.isEmpty()){
        ui->lb_notice_1->setText("Input Error All fields must be filled out");
        return;
    }


    Query_ShippingAdd.prepare("INSERT INTO Order_Details ( userId, totalPrice, first_name,last_name,street, apt, city, province, phoneNumber, shippingMethod)  VALUES ( :userId, :total, :firstname, :lastname, :streetadd, :Apt, :City, :Province, :phonenumber, :methodShipping)");
    Query_ShippingAdd.bindValue(":userId",USER_ID);
    Query_ShippingAdd.bindValue(":total",total);
    Query_ShippingAdd.bindValue(":firstname",firstname);
    Query_ShippingAdd.bindValue(":lastname",lastname);
    Query_ShippingAdd.bindValue(":streetadd",streetadd);
    Query_ShippingAdd.bindValue(":Apt",Apt);
    Query_ShippingAdd.bindValue(":City",City);
    Query_ShippingAdd.bindValue(":Province",Province);
    Query_ShippingAdd.bindValue(":phonenumber",phonenumber);
    Query_ShippingAdd.bindValue(":methodShipping",methodShipping);

    if(!Query_ShippingAdd.exec())
    {
        qDebug() << Query_ShippingAdd.lastError().text() << Query_ShippingAdd.lastQuery();
        ui->lb_notice_1->setText("error");
    }
    else
    {
        if(Query_ShippingAdd.numRowsAffected() > 0)
        {
            qDebug() <<"read was successful "<< Query_ShippingAdd.lastQuery();
            ui->lb_notice_1->setText("Successfull");
        }
        else
            qDebug() <<"Unable to Add new Item";
    }


    QSqlQuery fetchQuery(MyDB::getInstance()->getDBInstance());
    fetchQuery.prepare("SELECT productId, total, quantity FROM Order_Items_temp");
    if (!fetchQuery.exec()) {
        qDebug() << "Error fetching from Order_Items_temp:" << fetchQuery.lastError();
        db.rollback();
        return;
    }
    QSqlQuery deleteCart(MyDB::getInstance()->getDBInstance());
    deleteCart.prepare("DELETE FROM Cart_Item WHERE cartId= :CARTID AND productId = :PRODUCTID ");


    QSqlQuery insertQuery(MyDB::getInstance()->getDBInstance());
    insertQuery.prepare("INSERT INTO Order_Items (productId, total, quantity) VALUES (:productId, :total, :quantity)");

    while (fetchQuery.next()) {
        //deleteCart.next();

        QString productId = fetchQuery.value("productId").toString();
        double total = fetchQuery.value("total").toDouble();
        int quantity = fetchQuery.value("quantity").toInt();

        insertQuery.bindValue(":productId", productId);
        insertQuery.bindValue(":total", total);
        insertQuery.bindValue(":quantity", quantity);

        deleteCart.bindValue(":CARTID", CART_ID);
        deleteCart.bindValue(":PRODUCTID", productId);
        deleteCart.exec();

        if (!insertQuery.exec()) {
            qDebug() << "Failed to insert into Order_Items:" << &insertQuery;
        }
    }

    // Cập nhật số lượng:

    QSqlQuery queryUpdate(MyDB::getInstance()->getDBInstance());
    queryUpdate.prepare("SELECT productId, quantity FROM Order_Items_temp");

    if (!queryUpdate.exec()) {
        qDebug() << "Error fetching from Order_Items_temp:" << queryUpdate.lastError();
        db.rollback();
        return;
    }

    QSqlQuery updateQuantity(MyDB::getInstance()->getDBInstance());

    while (queryUpdate.next()) {
        QString productId = queryUpdate.value("productId").toString();
        int quantityPurchased = queryUpdate.value("quantity").toInt();

        // Kiểm tra số lượng hiện tại trong kho
        QSqlQuery checkStockQuery(MyDB::getInstance()->getDBInstance());
        checkStockQuery.prepare("SELECT productQuantity FROM Product WHERE productId = '"+productId+"'");

        if (!checkStockQuery.exec() || !checkStockQuery.next()) {
            qDebug() << "Failed to fetch stock details for productId:" << productId << checkStockQuery.lastError()<< checkStockQuery.lastQuery();
            db.rollback();
            return;
        }

        int currentStock = checkStockQuery.value(0).toInt();
        if (currentStock < quantityPurchased) {
            qDebug() << "Not enough stock for productId:" << productId;
            db.rollback();
            return;
        }

        // Cập nhật số lượng trong kho
        int newStock = currentStock - quantityPurchased;
        QString newStockString = QString::number(newStock);
        updateQuantity.prepare("UPDATE Product SET productQuantity = '"+newStockString+"' WHERE productId ='"+productId+"'");

        if (!updateQuantity.exec()) {
            qDebug() << "Failed to update stock for productId:" << productId << updateQuantity.lastError()<< updateQuantity.lastQuery();;
            db.rollback();
            return;
        }
    }

    if (!db.commit()) {
        qDebug() << "Failed to commit transaction" << db.lastError();
        db.rollback();
    } else {
        qDebug() << "Stock updated successfully";
        // Additional code to close the transaction or update UI
    }



    QSqlQuery deleteTable(MyDB::getInstance()->getDBInstance());

    deleteTable.exec("DELETE FROM Order_Items_temp");
}


void thanh_toan::on_pushButton_clicked()
{
    hide();
    emit returnShoppingCart();
}

