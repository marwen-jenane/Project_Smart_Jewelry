#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>



class connexion
{
private:
    QSqlDatabase db;
public:
    connexion();
    bool ouvrirconnexion();
    void fermerconnexion();
};

#endif // CONNEXION_H








