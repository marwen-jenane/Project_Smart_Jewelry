#include "stock.h"
#include <QSqlQuery>
#include <QtDebug>
stock::stock()
{
id=0; quantite=0; prix=0; type="";
}
stock::stock(int id,int quantite,int prix,QString type)
{this->id=id; this->quantite=quantite; this->prix=prix; this->type=type; }
int stock::getid(){return id;}
int stock::getquantite(){return quantite;}
int stock::getprix(){return prix;}
QString stock::gettype(){return type;}
void stock::setid(int id){this->id=id;}
void stock::setquantite(int quantite){this->quantite=quantite;}
void stock::setprix(int prix){this->prix=prix;}
void stock::settype(QString type){this->type=type;}
bool stock::ajouter()
{
    QSqlQuery query;
   QString id_string=QString::number(id);
   QString quantite_string=QString::number(quantite);
   QString prix_string=QString::number(prix);
   query.prepare("INSERT INTO stock(id, type, quantite, prix) "
                 "VALUES (:id, :type, :quantite, :prix)");
   query.bindValue(":id", id_string);
   query.bindValue(":type", type);
   query.bindValue(":quantite", quantite_string);
   query.bindValue(":prix", prix_string);
   return query.exec();
}

QSqlQueryModel*  stock::afficher()

{

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT* FROM stock");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("quantite"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
    return model;
}
bool stock::supprimer(int id)

{
    QSqlQuery query;
    query.prepare("Delete from stock where id=:id");
    query.bindValue(0,id);
    return query.exec();
}

bool stock::modifier(int id)
{
       QSqlQuery query;
       QString id_string=QString::number(id);
       QString quantite_string = QString::number(quantite);
       QString prix_string = QString::number(prix);
       query.prepare("UPDATE stock SET type=:type,quantite=:quantite,id=:id,prix=:prix WHERE id=:id ");
       query.bindValue(":id", id_string);
       query.bindValue(":quantite", quantite_string);
       query.bindValue(":prix", prix_string);
       query.bindValue(":type", type);
       return query.exec();
}
