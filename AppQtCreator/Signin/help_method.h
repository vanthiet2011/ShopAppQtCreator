#ifndef HELP_METHOD_H
#define HELP_METHOD_H

#include <QDialog>

namespace Ui {
class help_method;
}

class help_method : public QDialog
{
    Q_OBJECT

public:
    explicit help_method(QWidget *parent = nullptr);
    ~help_method();

private:
    Ui::help_method *ui;
};

#endif // HELP_METHOD_H
