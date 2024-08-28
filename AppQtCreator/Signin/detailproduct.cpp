#include "detailproduct.h"
#include "ui_detailproduct.h"

DetailProduct::DetailProduct(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DetailProduct)
{
    ui->setupUi(this);
}

DetailProduct::~DetailProduct()
{
    delete ui;
}
