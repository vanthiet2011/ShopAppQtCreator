#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QDialog>

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


#include "mydb.h"

namespace Ui {
class AddProduct;
}

class AddProduct : public QDialog
{
    Q_OBJECT

public:
    explicit AddProduct(QWidget *parent = nullptr);
    ~AddProduct();

private slots:
    void on_btnAdd_clicked();

    void on_pushButton_Browse_Image_clicked();

private:
    Ui::AddProduct *ui;

};

#endif // ADDPRODUCT_H
