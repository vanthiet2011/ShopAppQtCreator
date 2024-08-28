#ifndef HELP_SHIPPINGADD_H
#define HELP_SHIPPINGADD_H

#include <QDialog>

namespace Ui {
class help_shippingAdd;
}

class help_shippingAdd : public QDialog
{
    Q_OBJECT

public:
    explicit help_shippingAdd(QWidget *parent = nullptr);
    ~help_shippingAdd();

private:
    Ui::help_shippingAdd *ui;
};

#endif // HELP_SHIPPINGADD_H
