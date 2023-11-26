#include "connection.h"

Connection::Connection()
{

}


bool Connection::createconnection()
{
   QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
 db.setDatabaseName("Projet_cpp");//source de Donees OBDC
 db.setUserName("selim");//inserer nom de l'utilisateur
 db.setPassword("esprit18");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;

    return  test;
}
void Connection::closeconnection(){db.close();}
