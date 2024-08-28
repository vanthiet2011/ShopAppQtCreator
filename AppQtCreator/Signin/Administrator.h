#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
#include <QWidget>
#include "mydb.h"
#include "shop_display.h"
#include <QByteArray>
#include <QString>

class Administrator
{
public:
    Administrator(Shop_display *display, QWidget *parent = nullptr);
    ~Administrator();
    bool updateCatalog();
private:
    Shop_display *displayUI;
    QByteArray finalDataToSave;
    QString imagePath;
    void browseImage();
    bool addProductToDB(const QString &id, const QString &name, const QString &price, const QString &quantity, const QString &status, const QByteArray &imageData);

signals:

public slots:
};
#endif // ADMINISTRATOR_H
