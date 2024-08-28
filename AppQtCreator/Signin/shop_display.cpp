#include "shop_display.h"
#include "./ui_shop_display.h"

#include <QSignalMapper>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
#include <QTableWidgetItem>
#include <QDebug>


#include "Global.h"


Shop_display::Shop_display(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Shop_display)
{
    ui->setupUi(this);
    ptrAddProduct = new AddProduct();

    ptrDetailProduct = new DetailProduct();

}

Shop_display::~Shop_display()
{
    delete ui;
    delete ptrAddProduct;
    delete ptrDetailProduct;
}


void Shop_display::on_Button_Add_Data_clicked()
{
    // ptrAddDataProducts ->show();
    ptrAddProduct -> show();
}

void Shop_display::on_pushButton_Display_From_Database_clicked()
{
    QSqlQuery QueryGetImage(MyDB::getInstance()->getDBInstance());
    QueryGetImage.clear();
    QueryGetImage.prepare("SELECT * FROM Product ");// Query For Get Last Saved Image From Database.

    if (QueryGetImage.exec()) {
        qDebug() << "Get SQL Exec";
        ui->tableWidget_Image_LIst_From_Database->setRowCount(0); // Xóa tất cả các hàng hiện có

        // int rowNumber = 0;
        while (QueryGetImage.next()) {
            int rowNumber = ui->tableWidget_Image_LIst_From_Database->rowCount();
            ui->tableWidget_Image_LIst_From_Database->insertRow(rowNumber);
            // Lấy tên ảnh và dữ liệu từ cơ sở dữ liệu
            QString productId = QueryGetImage.value(0).toString();
            QString productName = QueryGetImage.value(1).toString();
            QString productPrice = QueryGetImage.value(2).toString();
            QByteArray productImageFromDatabase = QueryGetImage.value(3).toByteArray();
            QString productQuantity = QueryGetImage.value(4).toString();
            QString productStatus = QueryGetImage.value(5).toString();

            // Tải ảnh từ dữ liệu và kiểm tra
            QPixmap image;
            if (image.loadFromData(QByteArray::fromBase64(productImageFromDatabase), "JPG")) {
                // Tạo một ô QTableWidgetItem để hiển thị ảnh
                QTableWidgetItem *imageProduct = new QTableWidgetItem();

                imageProduct->setData(Qt::DecorationRole, image.scaled(400, 400, Qt::KeepAspectRatio));

                // ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productId));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productName));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber, 2, imageProduct);
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,1,new QTableWidgetItem(productPrice));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,3,new QTableWidgetItem(productQuantity));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,4,new QTableWidgetItem(productStatus));

                QPushButton *pushButton =new QPushButton("Add Cart");


                // ui->tableWidget_Image_LIst_From_Database->setCellWidget(rowNumber, 5, pushButton);



                pushButton->setProperty("productId", QueryGetImage.value(0).toString());

                // Kết nối tín hiệu clicked của nút với slot mới
                connect(pushButton, &QPushButton::clicked, [this, productId]() {
                    QSqlQuery Query_subtotal(MyDB::getInstance()->getDBInstance());
                    Query_subtotal.prepare("INSERT INTO Cart_Item (productId)  VALUES (:productId)");
                    Query_subtotal.bindValue(":productId", productId);
                    Query_subtotal.exec();

                });
                ++rowNumber;
            } else {
                qDebug() << "Failed to load image:" << productId;
            }
        }
        // Thiết lập kích thước mặc định cho header dọc
        ui->tableWidget_Image_LIst_From_Database->verticalHeader()->setDefaultSectionSize(400);
        // ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,200);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(1,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(2,400);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(3,100);
    } else {
        qDebug() << "SQL Exec ERROR:" << QueryGetImage.lastError().text();
    }
}

void Shop_display::on_on_btn_show_Jacket_clicked()
{
    QSqlQuery QueryGetImage(MyDB::getInstance()->getDBInstance());
    QueryGetImage.clear();
    QueryGetImage.prepare("SELECT * FROM Product WHERE productId LIKE 'J%' ");// Query For Get Last Saved Image From Database.

    if (QueryGetImage.exec()) {
        qDebug() << "Get SQL Exec";
        ui->tableWidget_Image_LIst_From_Database->setRowCount(0); // Xóa tất cả các hàng hiện có

        // int rowNumber = 0;
        while (QueryGetImage.next()) {
            int rowNumber = ui->tableWidget_Image_LIst_From_Database->rowCount();
            ui->tableWidget_Image_LIst_From_Database->insertRow(rowNumber);
            // Lấy tên ảnh và dữ liệu từ cơ sở dữ liệu
            QString productId = QueryGetImage.value(0).toString();
            QString productName = QueryGetImage.value(1).toString();
            QString productPrice = QueryGetImage.value(2).toString();
            QByteArray productImageFromDatabase = QueryGetImage.value(3).toByteArray();
            QString productQuantity = QueryGetImage.value(4).toString();
            QString productStatus = QueryGetImage.value(5).toString();

            // Tải ảnh từ dữ liệu và kiểm tra
            QPixmap image;
            if (image.loadFromData(QByteArray::fromBase64(productImageFromDatabase), "JPG")) {
                // Tạo một ô QTableWidgetItem để hiển thị ảnh
                QTableWidgetItem *imageProduct = new QTableWidgetItem();

                imageProduct->setData(Qt::DecorationRole, image.scaled(400, 400, Qt::KeepAspectRatio));

                // ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productId));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productName));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber, 2, imageProduct);
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,1,new QTableWidgetItem(productPrice));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,3,new QTableWidgetItem(productQuantity));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,4,new QTableWidgetItem(productStatus));

                QPushButton *pushButton =new QPushButton("Add Cart");


                // ui->tableWidget_Image_LIst_From_Database->setCellWidget(rowNumber, 5, pushButton);



                pushButton->setProperty("productId", QueryGetImage.value(0).toString());

                // Kết nối tín hiệu clicked của nút với slot mới
                connect(pushButton, &QPushButton::clicked, [this, productId]() {
                    QSqlQuery Query_subtotal(MyDB::getInstance()->getDBInstance());
                    Query_subtotal.prepare("INSERT INTO Cart_Item (productId)  VALUES (:productId)");
                    Query_subtotal.bindValue(":productId", productId);
                    Query_subtotal.exec();

                });
                ++rowNumber;
            } else {
                qDebug() << "Failed to load image:" << productId;
            }
        }
        // Thiết lập kích thước mặc định cho header dọc
        ui->tableWidget_Image_LIst_From_Database->verticalHeader()->setDefaultSectionSize(400);
        // ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,200);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(1,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(2,400);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(3,100);
    } else {
        qDebug() << "SQL Exec ERROR:" << QueryGetImage.lastError().text();
    }
}


void Shop_display::on_on_btn_show_Tshirt_clicked()
{
    QSqlQuery QueryGetImage(MyDB::getInstance()->getDBInstance());
    QueryGetImage.clear();
    QueryGetImage.prepare("SELECT * FROM Product WHERE productId LIKE 'SHIRT%' ");// Query For Get Last Saved Image From Database.

    if (QueryGetImage.exec()) {
        qDebug() << "Get SQL Exec";
        ui->tableWidget_Image_LIst_From_Database->setRowCount(0); // Xóa tất cả các hàng hiện có

        // int rowNumber = 0;
        while (QueryGetImage.next()) {
            int rowNumber = ui->tableWidget_Image_LIst_From_Database->rowCount();
            ui->tableWidget_Image_LIst_From_Database->insertRow(rowNumber);
            // Lấy tên ảnh và dữ liệu từ cơ sở dữ liệu
            QString productId = QueryGetImage.value(0).toString();
            QString productName = QueryGetImage.value(1).toString();
            QString productPrice = QueryGetImage.value(2).toString();
            QByteArray productImageFromDatabase = QueryGetImage.value(3).toByteArray();
            QString productQuantity = QueryGetImage.value(4).toString();
            QString productStatus = QueryGetImage.value(5).toString();

            // Tải ảnh từ dữ liệu và kiểm tra
            QPixmap image;
            if (image.loadFromData(QByteArray::fromBase64(productImageFromDatabase), "JPG")) {
                // Tạo một ô QTableWidgetItem để hiển thị ảnh
                QTableWidgetItem *imageProduct = new QTableWidgetItem();

                imageProduct->setData(Qt::DecorationRole, image.scaled(400, 400, Qt::KeepAspectRatio));

                // ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productId));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productName));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber, 2, imageProduct);
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,1,new QTableWidgetItem(productPrice));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,3,new QTableWidgetItem(productQuantity));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,4,new QTableWidgetItem(productStatus));

                QPushButton *pushButton =new QPushButton("Add Cart");


                // ui->tableWidget_Image_LIst_From_Database->setCellWidget(rowNumber, 5, pushButton);



                pushButton->setProperty("productId", QueryGetImage.value(0).toString());

                // Kết nối tín hiệu clicked của nút với slot mới
                connect(pushButton, &QPushButton::clicked, [this, productId]() {
                    QSqlQuery Query_subtotal(MyDB::getInstance()->getDBInstance());
                    Query_subtotal.prepare("INSERT INTO Cart_Item (productId)  VALUES (:productId)");
                    Query_subtotal.bindValue(":productId", productId);
                    Query_subtotal.exec();

                });
                ++rowNumber;
            } else {
                qDebug() << "Failed to load image:" << productId;
            }
        }
        // Thiết lập kích thước mặc định cho header dọc
        ui->tableWidget_Image_LIst_From_Database->verticalHeader()->setDefaultSectionSize(400);
        // ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,200);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(1,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(2,400);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(3,100);
    } else {
        qDebug() << "SQL Exec ERROR:" << QueryGetImage.lastError().text();
    }
}


void Shop_display::on_on_btn_show_Polo_clicked()
{
    QSqlQuery QueryGetImage(MyDB::getInstance()->getDBInstance());
    QueryGetImage.clear();
    QueryGetImage.prepare("SELECT * FROM Product WHERE productId LIKE 'POLO%' ");// Query For Get Last Saved Image From Database.

    if (QueryGetImage.exec()) {
        qDebug() << "Get SQL Exec";
        ui->tableWidget_Image_LIst_From_Database->setRowCount(0); // Xóa tất cả các hàng hiện có

        // int rowNumber = 0;
        while (QueryGetImage.next()) {
            int rowNumber = ui->tableWidget_Image_LIst_From_Database->rowCount();
            ui->tableWidget_Image_LIst_From_Database->insertRow(rowNumber);
            // Lấy tên ảnh và dữ liệu từ cơ sở dữ liệu
            QString productId = QueryGetImage.value(0).toString();
            QString productName = QueryGetImage.value(1).toString();
            QString productPrice = QueryGetImage.value(2).toString();
            QByteArray productImageFromDatabase = QueryGetImage.value(3).toByteArray();
            QString productQuantity = QueryGetImage.value(4).toString();
            QString productStatus = QueryGetImage.value(5).toString();

            // Tải ảnh từ dữ liệu và kiểm tra
            QPixmap image;
            if (image.loadFromData(QByteArray::fromBase64(productImageFromDatabase), "JPG")) {
                // Tạo một ô QTableWidgetItem để hiển thị ảnh
                QTableWidgetItem *imageProduct = new QTableWidgetItem();

                imageProduct->setData(Qt::DecorationRole, image.scaled(400, 400, Qt::KeepAspectRatio));

                // ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productId));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productName));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber, 2, imageProduct);
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,1,new QTableWidgetItem(productPrice));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,3,new QTableWidgetItem(productQuantity));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,4,new QTableWidgetItem(productStatus));

                QPushButton *pushButton =new QPushButton("Add Cart");


                // ui->tableWidget_Image_LIst_From_Database->setCellWidget(rowNumber, 5, pushButton);



                pushButton->setProperty("productId", QueryGetImage.value(0).toString());

                // Kết nối tín hiệu clicked của nút với slot mới
                connect(pushButton, &QPushButton::clicked, [this, productId]() {
                    QSqlQuery Query_subtotal(MyDB::getInstance()->getDBInstance());
                    Query_subtotal.prepare("INSERT INTO Cart_Item (productId)  VALUES (:productId)");
                    Query_subtotal.bindValue(":productId", productId);
                    Query_subtotal.exec();

                });
                ++rowNumber;
            } else {
                qDebug() << "Failed to load image:" << productId;
            }
        }
        // Thiết lập kích thước mặc định cho header dọc
        ui->tableWidget_Image_LIst_From_Database->verticalHeader()->setDefaultSectionSize(400);
        // ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,200);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(1,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(2,400);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(3,100);
    } else {
        qDebug() << "SQL Exec ERROR:" << QueryGetImage.lastError().text();
    }
}


void Shop_display::on_on_btn_show_Pant_clicked()
{
    QSqlQuery QueryGetImage(MyDB::getInstance()->getDBInstance());
    QueryGetImage.clear();
    QueryGetImage.prepare("SELECT * FROM Product WHERE productId LIKE 'PANT%' ");// Query For Get Last Saved Image From Database.

    if (QueryGetImage.exec()) {
        qDebug() << "Get SQL Exec";
        ui->tableWidget_Image_LIst_From_Database->setRowCount(0); // Xóa tất cả các hàng hiện có

        // int rowNumber = 0;
        while (QueryGetImage.next()) {
            int rowNumber = ui->tableWidget_Image_LIst_From_Database->rowCount();
            ui->tableWidget_Image_LIst_From_Database->insertRow(rowNumber);
            // Lấy tên ảnh và dữ liệu từ cơ sở dữ liệu
            QString productId = QueryGetImage.value(0).toString();
            QString productName = QueryGetImage.value(1).toString();
            QString productPrice = QueryGetImage.value(2).toString();
            QByteArray productImageFromDatabase = QueryGetImage.value(3).toByteArray();
            QString productQuantity = QueryGetImage.value(4).toString();
            QString productStatus = QueryGetImage.value(5).toString();

            // Tải ảnh từ dữ liệu và kiểm tra
            QPixmap image;
            if (image.loadFromData(QByteArray::fromBase64(productImageFromDatabase), "JPG")) {
                // Tạo một ô QTableWidgetItem để hiển thị ảnh
                QTableWidgetItem *imageProduct = new QTableWidgetItem();

                imageProduct->setData(Qt::DecorationRole, image.scaled(400, 400, Qt::KeepAspectRatio));

                // ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productId));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productName));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber, 2, imageProduct);
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,1,new QTableWidgetItem(productPrice));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,3,new QTableWidgetItem(productQuantity));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,4,new QTableWidgetItem(productStatus));

                QPushButton *pushButton =new QPushButton("Add Cart");


                // ui->tableWidget_Image_LIst_From_Database->setCellWidget(rowNumber, 5, pushButton);



                pushButton->setProperty("productId", QueryGetImage.value(0).toString());

                // Kết nối tín hiệu clicked của nút với slot mới
                connect(pushButton, &QPushButton::clicked, [this, productId]() {
                    QSqlQuery Query_subtotal(MyDB::getInstance()->getDBInstance());
                    Query_subtotal.prepare("INSERT INTO Cart_Item (productId)  VALUES (:productId)");
                    Query_subtotal.bindValue(":productId", productId);
                    Query_subtotal.exec();

                });
                ++rowNumber;
            } else {
                qDebug() << "Failed to load image:" << productId;
            }
        }
        // Thiết lập kích thước mặc định cho header dọc
        ui->tableWidget_Image_LIst_From_Database->verticalHeader()->setDefaultSectionSize(400);
        // ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,200);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(1,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(2,400);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(3,100);
    } else {
        qDebug() << "SQL Exec ERROR:" << QueryGetImage.lastError().text();
    }
}


void Shop_display::on_on_btn_show_Short_clicked()
{
    QSqlQuery QueryGetImage(MyDB::getInstance()->getDBInstance());
    QueryGetImage.clear();
    QueryGetImage.prepare("SELECT * FROM Product WHERE productId LIKE 'SHORT%' ");// Query For Get Last Saved Image From Database.

    if (QueryGetImage.exec()) {
        qDebug() << "Get SQL Exec";
        ui->tableWidget_Image_LIst_From_Database->setRowCount(0); // Xóa tất cả các hàng hiện có

        // int rowNumber = 0;
        while (QueryGetImage.next()) {
            int rowNumber = ui->tableWidget_Image_LIst_From_Database->rowCount();
            ui->tableWidget_Image_LIst_From_Database->insertRow(rowNumber);
            // Lấy tên ảnh và dữ liệu từ cơ sở dữ liệu
            QString productId = QueryGetImage.value(0).toString();
            QString productName = QueryGetImage.value(1).toString();
            QString productPrice = QueryGetImage.value(2).toString();
            QByteArray productImageFromDatabase = QueryGetImage.value(3).toByteArray();
            QString productQuantity = QueryGetImage.value(4).toString();
            QString productStatus = QueryGetImage.value(5).toString();

            // Tải ảnh từ dữ liệu và kiểm tra
            QPixmap image;
            if (image.loadFromData(QByteArray::fromBase64(productImageFromDatabase), "JPG")) {
                // Tạo một ô QTableWidgetItem để hiển thị ảnh
                QTableWidgetItem *imageProduct = new QTableWidgetItem();

                imageProduct->setData(Qt::DecorationRole, image.scaled(400, 400, Qt::KeepAspectRatio));

                // ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productId));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productName));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber, 2, imageProduct);
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,1,new QTableWidgetItem(productPrice));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,3,new QTableWidgetItem(productQuantity));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,4,new QTableWidgetItem(productStatus));

                QPushButton *pushButton =new QPushButton("Add Cart");


                // ui->tableWidget_Image_LIst_From_Database->setCellWidget(rowNumber, 5, pushButton);



                pushButton->setProperty("productId", QueryGetImage.value(0).toString());

                // Kết nối tín hiệu clicked của nút với slot mới
                connect(pushButton, &QPushButton::clicked, [this, productId]() {
                    QSqlQuery Query_subtotal(MyDB::getInstance()->getDBInstance());
                    Query_subtotal.prepare("INSERT INTO Cart_Item (productId)  VALUES (:productId)");
                    Query_subtotal.bindValue(":productId", productId);
                    Query_subtotal.exec();

                });
                ++rowNumber;
            } else {
                qDebug() << "Failed to load image:" << productId;
            }
        }
        // Thiết lập kích thước mặc định cho header dọc
        ui->tableWidget_Image_LIst_From_Database->verticalHeader()->setDefaultSectionSize(400);
        // ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,200);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(1,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(2,400);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(3,100);
    } else {
        qDebug() << "SQL Exec ERROR:" << QueryGetImage.lastError().text();
    }
}


void Shop_display::on_on_pushButton_Search_clicked()
{
    // QSqlQuery QueryGetImage(MyDB::getInstance()->getDBInstance());
    // QueryGetImage.clear();
    QString searchTerm = ui->searchInput->text(); // Assuming you have a QLineEdit with the objectName 'searchInput'
    QSqlQuery QueryGetImage(MyDB::getInstance()->getDBInstance());
    QueryGetImage.clear();
    QueryGetImage.prepare("SELECT * FROM Product WHERE productName LIKE :searchTerm");
    QueryGetImage.bindValue(":searchTerm", '%' + searchTerm + '%');

    if (QueryGetImage.exec()) {
        qDebug() << "Get SQL Exec";
        ui->tableWidget_Image_LIst_From_Database->setRowCount(0); // Xóa tất cả các hàng hiện có

        // int rowNumber = 0;
        while (QueryGetImage.next()) {
            int rowNumber = ui->tableWidget_Image_LIst_From_Database->rowCount();
            ui->tableWidget_Image_LIst_From_Database->insertRow(rowNumber);
            // Lấy tên ảnh và dữ liệu từ cơ sở dữ liệu
            QString productId = QueryGetImage.value(0).toString();
            QString productName = QueryGetImage.value(1).toString();
            QString productPrice = QueryGetImage.value(2).toString();
            QByteArray productImageFromDatabase = QueryGetImage.value(3).toByteArray();
            QString productQuantity = QueryGetImage.value(4).toString();
            QString productStatus = QueryGetImage.value(5).toString();

            // Tải ảnh từ dữ liệu và kiểm tra
            QPixmap image;
            if (image.loadFromData(QByteArray::fromBase64(productImageFromDatabase), "JPG")) {
                // Tạo một ô QTableWidgetItem để hiển thị ảnh
                QTableWidgetItem *imageProduct = new QTableWidgetItem();

                imageProduct->setData(Qt::DecorationRole, image.scaled(400, 400, Qt::KeepAspectRatio));

                // ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productId));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,0,new QTableWidgetItem(productName));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber, 2, imageProduct);
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,1,new QTableWidgetItem(productPrice));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,3,new QTableWidgetItem(productQuantity));
                ui->tableWidget_Image_LIst_From_Database->setItem(rowNumber,4,new QTableWidgetItem(productStatus));

                QPushButton *pushButton =new QPushButton("Add Cart");


                // ui->tableWidget_Image_LIst_From_Database->setCellWidget(rowNumber, 5, pushButton);



                pushButton->setProperty("productId", QueryGetImage.value(0).toString());

                // Kết nối tín hiệu clicked của nút với slot mới
                connect(pushButton, &QPushButton::clicked, [this, productId]() {
                    QSqlQuery Query_subtotal(MyDB::getInstance()->getDBInstance());
                    Query_subtotal.prepare("INSERT INTO Cart_Item (productId)  VALUES (:productId)");
                    Query_subtotal.bindValue(":productId", productId);
                    Query_subtotal.exec();

                });
                ++rowNumber;
            } else {
                qDebug() << "Failed to load image:" << productId;
            }
        }
        // Thiết lập kích thước mặc định cho header dọc
        ui->tableWidget_Image_LIst_From_Database->verticalHeader()->setDefaultSectionSize(400);
        // ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(0,200);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(1,150);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(2,400);
        ui->tableWidget_Image_LIst_From_Database->setColumnWidth(3,100);
    } else {
        qDebug() << "SQL Exec ERROR:" << QueryGetImage.lastError().text();
    }
}


void Shop_display::on_on_pushButton_Menu_clicked()
{
    // Assume the expanded size for widget_2 and the table widget
    QRect expandedWidget2Geometry = QRect(10, 210, 210, 310);
    QRect expandedTableWidgetGeometry = QRect(250, 210, 1220, 580);

    // Assume the collapsed size for widget_2 and the table widget
    QRect collapsedWidget2Geometry = QRect(10, 210, 0, 350);  // Set the width to 0 for collapsing
    QRect collapsedTableWidgetGeometry = QRect(80, 210, 1390, 580);

    // Check current size to determine if we are expanding or collapsing
    bool isExpanded = ui->widget_2->width() > 0;

    animation_1 = new QPropertyAnimation(ui->tableWidget_Image_LIst_From_Database, "geometry");
    animation_2 = new QPropertyAnimation(ui->widget_2, "geometry");
    animation_1->setDuration(300);
    animation_2->setDuration(300);

    animation_1->setStartValue(ui->tableWidget_Image_LIst_From_Database->geometry());
    animation_2->setStartValue(ui->widget_2->geometry());

    if (isExpanded) {
        // If expanded, we collapse
        animation_1->setEndValue(collapsedTableWidgetGeometry);
        animation_2->setEndValue(collapsedWidget2Geometry);
    } else {
        // If collapsed, we expand
        animation_1->setEndValue(expandedTableWidgetGeometry);
        animation_2->setEndValue(expandedWidget2Geometry);
    }

    animation_1->start();
    animation_2->start();
}





void Shop_display::on_pushButton_3_clicked()
{
    hide();
    emit returnToLogin();
}

