#include "help_shippingadd.h"
#include "ui_help_shippingadd.h"

help_shippingAdd::help_shippingAdd(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::help_shippingAdd)
{
    ui->setupUi(this);
}

help_shippingAdd::~help_shippingAdd()
{
    delete ui;
}
