#include "shoppingcart.h"
#include "./ui_shoppingcart.h"
//#define Path_to_DB "E:/Zalo/ShoppingCartUpdata/ShoppingData(1).db"
#include "thanh_toan.h"
#include "shoppingcart.h"
#include "thanh_toan.h"
#include "Global.h"
int totalPriceSum = 0;
ShoppingCart::ShoppingCart(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShoppingCart)
{
    ui->setupUi(this);
    // DBConnection=QSqlDatabase::addDatabase("QSQLITE");
    // DBConnection.setDatabaseName(Path_to_DB);
    // if(DBConnection.open()){
    //     qDebug()<<"Database is connnected!";
    // }
    // else{
    //     qDebug()<<"Database is not connected";
    // }
}

ShoppingCart::~ShoppingCart()
{
    delete ui;
}

void ShoppingCart::on_checkBtn_clicked()
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QString cartid = QString::number(CART_ID);
    query.prepare("SELECT Product.productName, Product.productPrice "
                  "FROM Product "
                  "INNER JOIN Cart_Item ON Product.productId = Cart_Item.productId "
                  " WHERE Cart_Item.cartId = '"+cartid+"'");
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        return;
    }

    int row = 0; // Số hàng hiện tại trong tableWidget
    ui->productTableWidget->setRowCount(row);

    while (query.next()) {
        ui->productTableWidget->setRowCount(row+1);
        QString productName = query.value("productName").toString();
        int price = query.value("productPrice").toInt();


        // Thêm sản phẩm vào tableWidget
        QTableWidgetItem *nameProduct = new QTableWidgetItem(productName);
        ui->productTableWidget->setItem(row, 0, nameProduct);

        //Thêm giá sản phẩmItem
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(price));
        ui->productTableWidget->setItem(row, 2, priceItem);

        //Thêm spinbox cho quantity
        QSpinBox *newSpinBox = new QSpinBox();
        newSpinBox->setMinimum(1);
        newSpinBox->setMaximum(100);
        newSpinBox->setValue(0);
        ui->productTableWidget->setCellWidget(row, 1, newSpinBox);

        // Cập nhật giá trị khi spinbox thay đổi
        connect(newSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
            int totalPrice = value * price;
            QTableWidgetItem *total = new QTableWidgetItem(QString::number(totalPrice));
            ui->productTableWidget->setItem(row, 3, total);

            int totalSpinBoxValue = 0;
            for (int i = 0; i < ui->productTableWidget->rowCount(); ++i) {
                QWidget *widget = ui->productTableWidget->cellWidget(i, 1);
                if (widget) {
                    QSpinBox *spinBox = qobject_cast<QSpinBox*>(widget);
                    if (spinBox) {
                        totalSpinBoxValue += spinBox->value();
                    }
                }
            }
            ui->quantitySummary->setText(QString::number(totalSpinBoxValue));

            // Tính tổng giá trị của tất cả các sản phẩm
            totalPriceSum = 0;
            for (int i = 0; i < ui->productTableWidget->rowCount(); ++i) {
                QTableWidgetItem *item = ui->productTableWidget->item(i, 3);
                if (item) {
                    totalPriceSum += item->text().toInt();
                }
            }
            ui->priceSummary->setText("$" + QString::number(totalPriceSum));
        });

        row++;
    }
}


void ShoppingCart::on_checkOutBtn_clicked()
{
    QSqlDatabase db = MyDB::getInstance()->getDBInstance();
    if (!db.transaction()) {
        qDebug() << "Failed to start transaction";
        return;
    }
    QSqlQuery productQuery(db);
    QSqlQuery cartItemQuery(db);
    QSqlQuery insertQuery(db);
    QSqlQuery insertCartId(db);
    for (int row = 0; row < ui->productTableWidget->rowCount(); ++row) {
        QString productName = ui->productTableWidget->item(row, 0)->text();
        QSpinBox *spinBox = qobject_cast<QSpinBox*>(ui->productTableWidget->cellWidget(row, 1));
        int quantity = spinBox ? spinBox->value() : 0;
        double total = ui->productTableWidget->item(row, 3)->text().toDouble();

        // Retrieve the productId from the Product table
        productQuery.prepare("SELECT productId FROM Product WHERE productName = :productName");
        productQuery.bindValue(":productName", productName);
        if (!productQuery.exec() || !productQuery.next()) {
            qDebug() << "Failed to fetch productId for" << productName << productQuery.lastError();
            db.rollback();
            return;
        }
        QString productId = productQuery.value(0).toString();

        // Retrieve id and cartId from the Cart_Item table
        cartItemQuery.prepare("SELECT id, cartId FROM Cart_Item WHERE productId = :productId");
        cartItemQuery.bindValue(":productId", productId);
        if (!cartItemQuery.exec() || !cartItemQuery.next()) {
            qDebug() << "Failed to fetch cart item details for productId" << productId << cartItemQuery.lastError();
            db.rollback();
            return;
        }
        int cartId = cartItemQuery.value(1).toInt();
        int id = cartItemQuery.value(0).toInt();

        // Insert data into Order_Items_temp
        insertQuery.prepare("INSERT INTO Order_Items_temp (productId, productName, quantity, total, id, cartId) "
                            "VALUES (:productId, :productName, :quantity, :total, :id, :cartId)");
        insertQuery.bindValue(":productId", productId);
        insertQuery.bindValue(":productName", productName);
        insertQuery.bindValue(":quantity", quantity);
        insertQuery.bindValue(":total", total);
        insertQuery.bindValue(":id", id);
        insertQuery.bindValue(":cartId", cartId);
        if (!insertQuery.exec()) {
            qDebug() << "Failed to insert row" << row << insertQuery.lastError();
            db.rollback();
            return;
        }
        insertCartId.prepare("UPDATE Cart_Item SET quantity = :quantity WHERE productId = :productId AND cartId = :cartId");
        insertCartId.bindValue(":productId",productId);
        insertCartId.bindValue(":cartId", cartId);
        insertCartId.bindValue(":quantity", quantity);
        if (!insertCartId.exec()) {
            qDebug() << "Failed to insert Cart_Item row" << row << insertQuery.lastError();
            return;
        }
    }

    if (!db.commit()) {
        qDebug() << "Failed to commit transaction" << db.lastError();
        db.rollback();
    } else {
        hide();
        thanhToan = new thanh_toan();
        connect(thanhToan, &::thanh_toan::returnShoppingCart, this, &ShoppingCart::show);
        thanhToan->show();
    }
}


void ShoppingCart::on_pushButton_clicked()
{
    hide();
    emit returnShoppingDisplay();
}

