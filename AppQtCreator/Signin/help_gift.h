#ifndef HELP_GIFT_H
#define HELP_GIFT_H

#include <QDialog>

namespace Ui {
class help_gift;
}

class help_gift : public QDialog
{
    Q_OBJECT

public:
    explicit help_gift(QWidget *parent = nullptr);
    ~help_gift();

private:
    Ui::help_gift *ui;
};

#endif // HELP_GIFT_H
