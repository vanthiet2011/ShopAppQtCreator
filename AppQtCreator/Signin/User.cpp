// user.cpp
#include "User.h"
#include "global.h"

User::User(QObject *parent) : QObject(parent)
{
}

User::~User()
{
}

bool User::loginUser(QString username, QString password, bool isAdmin)
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.clear();
    if (isAdmin) {
        query.prepare("SELECT * FROM Admin WHERE adminId = :username AND password = :password");
    } else {
        query.prepare("SELECT * FROM User WHERE userId = :username AND password = :password");
    }
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
        return false;
    } else {
        if (query.next() == 1) {
            qDebug() << "Login successful";
            USER_ID = username;
            return true;
        } else {
            qDebug() << "Login failed";
            return false;
        }
    }
}

bool User::registerUser(QString username, QString password, QString registerDate, QString firstName, QString lastName, QString telephone)
{
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    query.clear();

    // Kiểm tra tài khoản có bị trùng lặp không.
    query.prepare("SELECT * FROM User WHERE userId = :username");
    query.bindValue(":username", username);
    if (!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
        return false;
    }
    if (query.next()) {
        return false; // Tài khoản đã tồn tại
    }

    // Nếu không có tài khoản trùng lặp, tiến hành đăng ký.
    query.prepare("INSERT INTO User (userId, password, registerDate, firstName, lastName, telephone) VALUES (:username, :password, :registerDate, :firstname, :lastname, :telephone)");
    query.bindValue(":username", username);
    query.bindValue(":password", password); // Lưu ý: nên mã hóa mật khẩu trước khi lưu.
    query.bindValue(":telephone", telephone);
    query.bindValue(":registerDate", registerDate);
    query.bindValue(":firstname", firstName);
    query.bindValue(":lastname", lastName);

    if (!query.exec()) {
        qDebug() << query.lastError().text() << query.lastQuery();
        return false;
    } else {
        // Tạo giỏ hàng mới cho người dùng
        query.prepare("INSERT INTO Cart (userId) VALUES (:username)");
        query.bindValue(":username", username);
        if (!query.exec()) {
            qDebug() << query.lastError().text() << query.lastQuery();
            return false; // Lỗi tạo giỏ hàng
        }
        return true; // Đăng ký thành công
    }
}
