#ifndef STOCK_H
#define STOCK_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class stock
{

public:
    stock();
    stock(int,int,int,QString);
    int getid();
    int getquantite();
    int getprix();
    QString gettype();
    void setid(int);
    void setquantite(int);
    void setprix(int);
    void settype(QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);


private:
    int id, quantite;
    int prix ;
    QString type;

};

#endif // STOCK_H
