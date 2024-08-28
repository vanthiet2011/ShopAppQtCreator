#include "Administrator.h"
#include <QFileDialog>
#include <QBuffer>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "global.h"



Administrator::Administrator(Shop_display *display)
    : displayUI(display) {
    // Nếu Shop_display đã khởi tạo UI, không cần thiết lập lại UI
}


Administrator::~Administrator() {
}

bool Administrator::updateCatalog() {
    browseImage();  // Lấy và xử lý hình ảnh

    QString id = displayUI->ui->txtID->text();  // Truy cập trực tiếp thông qua displayUI
    QString name = displayUI->ui->txtName->text();
    QString price = displayUI->ui->txtPurchasePrice->text();
    QString quantity = displayUI->ui->txtQuantity->text();
    QString status = displayUI->ui->cmbStatus->currentText();

    return addProductToDB(id, name, price, quantity, status, finalDataToSave);
}

void Administrator::browseImage() {
    imagePath = QFileDialog::getOpenFileName(displayUI, tr("Select Image"), QCoreApplication::applicationDirPath(), tr("JPG Files (*.jpg)"));
    QPixmap image(imagePath);

    QBuffer imageBufferData;
    if (imageBufferData.open(QIODevice::ReadWrite)) {
        image.save(&imageBufferData, "JPG");
    }
    finalDataToSave = imageBufferData.buffer().toBase64();
    displayUI->ui->lbl_Image_Browse->setPixmap(image);
}

bool Administrator::addProductToDB(const QString &id, const QString &name, const QString &price, const QString &quantity, const QString &status, const QByteArray &imageData) {
    QSqlDatabase::database().transaction();

    QSqlQuery query(QSqlDatabase::database());
    query.prepare("INSERT INTO Product(productId, productName, productPrice, productQuantity, productStatus, productImage) VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(id);
    query.addBindValue(name);
    query.addBindValue(price);
    query.addBindValue(quantity);
    query.addBindValue(status);
    query.addBindValue(imageData);

    if (!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
        return false;
    }

    QSqlDatabase::database().commit();
    return true;
}
