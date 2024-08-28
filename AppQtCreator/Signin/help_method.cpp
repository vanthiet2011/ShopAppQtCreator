#include "help_method.h"
#include "ui_help_method.h"

help_method::help_method(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::help_method)
{
    ui->setupUi(this);
}

help_method::~help_method()
{
    delete ui;
}
