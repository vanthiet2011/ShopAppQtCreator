#ifndef USER_H
#define USER_H

#include <QObject>
#include "mydb.h"

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    ~User();

    bool loginUser(QString username, QString password, bool isAdmin);
    bool registerUser(QString username, QString password, QString registerDate, QString firstName, QString lastName, QString telephone);

signals:

public slots:
};
#endif // USER_H
