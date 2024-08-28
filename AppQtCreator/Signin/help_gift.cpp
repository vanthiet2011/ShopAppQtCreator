#include "help_gift.h"
#include "ui_help_gift.h"

help_gift::help_gift(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::help_gift)
{
    ui->setupUi(this);
}

help_gift::~help_gift()
{
    delete ui;
}
