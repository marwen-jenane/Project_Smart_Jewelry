#include "connexion.h"

connexion::connexion()
{

}


bool connexion::ouvrirconnexion()

{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projetcpp");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("HAZEM007?");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void connexion::fermerconnexion(){db.close();}
