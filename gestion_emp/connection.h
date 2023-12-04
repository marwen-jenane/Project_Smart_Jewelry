#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql/QSqlDatabase>

class Connection
{
    QSqlDatabase db;

 public :
    Connection();
    bool createconnection();
    void closeconnection();
};


#endif // CONNECTION_H
