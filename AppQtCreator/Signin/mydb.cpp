#include "mydb.h"
#define Path_to_DB "D:/C++/Signin/ShoppingData.db"
MyDB* MyDB::instance = nullptr;



extern QString USER_ID;
extern int CART_ID ;


MyDB::MyDB()
{
    init();
}
void MyDB::init()
{
    qDebug() << "in init()";
    db = QSqlDatabase::addDatabase("QSQLITE", "Data");
    db.setDatabaseName(Path_to_DB);

    if(QFile::exists(Path_to_DB))
        qDebug() << "DB file exist";
    else
        qDebug() << "DB file doesn't exists";

    if (!db.open())
        qDebug() << db.lastError().text();
    else
        qDebug() << "Database loaded successfull!";

}

MyDB *MyDB::getInstance()
{
    qDebug() << "in MyDB::getInstance()";

    if(instance == nullptr)
        instance = new MyDB();

    return instance;
}

QSqlDatabase MyDB::getDBInstance()
{
    qDebug() <<"in getDBInstance()";
    return db;
}

void MyDB::ResetInstance()
{
    qDebug() << "deleting instance of MyDB";
    delete instance;
    instance = nullptr;
}






MyDB::~MyDB()
{
    qDebug() << "closing database connection";
    db.close();
}

