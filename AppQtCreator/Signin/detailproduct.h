#ifndef DETAILPRODUCT_H
#define DETAILPRODUCT_H

#include <QDialog>

namespace Ui {
class DetailProduct;
}

class DetailProduct : public QDialog
{
    Q_OBJECT

public:
    explicit DetailProduct(QWidget *parent = nullptr);
    ~DetailProduct();

private:
    Ui::DetailProduct *ui;
};

#endif // DETAILPRODUCT_H
