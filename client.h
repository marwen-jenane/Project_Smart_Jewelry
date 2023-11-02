#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQueryModel>


class Client
{
public:
    Client();
    Client(int,QString,QString,QString,QString);
    int getcin();
    QString getnom();
    QString getprenom();
    QString getadresse();
    QString getmail();
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void setmail(QString);
    bool ajouter();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    bool modifier();


private:
    int cin;
    QString nom,prenom,mail,adresse;
};

#endif // CLIENT_H

