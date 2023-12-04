#include "connection.h"
#include <QtSql/QSqlDatabase>

Connection::Connection(){}

bool Connection::createconnection()
{
    bool test;
    test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("jewerly");
    db.setUserName("mariem");
    db.setPassword("mariem");


    if (db.open())
        test=true;
    return test;
}

void Connection::closeconnection()
{
    db.close();
}
