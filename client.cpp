#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include<QObject>

Client::Client()
{
    cin=0;nom=" ";prenom=" ";adresse=" ";mail=" ";
}

Client::Client(int cin,QString nom,QString prenom,QString adresse,QString mail)
{
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;
    this->mail=mail;
}

int Client::getcin(){return cin;}
QString Client::getnom(){return nom;}
QString Client::getprenom(){return prenom;}
QString Client::getadresse(){return nom;}
QString Client::getmail(){return prenom;}
void Client::setcin(int cin){this->cin=cin;}
void Client::setnom(QString nom){this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setadresse(QString adresse){this->adresse=adresse;}
void Client::setmail(QString mail){this->mail=mail;}

bool Client::ajouter()
{   bool test=false;
    QSqlQuery query;
    QString cin_string=QString::number(cin);
          query.prepare("INSERT INTO client (cin, nom, prenom, adresse, mail) "
                        "VALUES (:cin, :nom, :prenom, :adresse, :mail)");
          query.bindValue(":cin", cin_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":adresse", adresse);
          query.bindValue(":mail", mail);
          test=query.exec();
    return test;
}

bool Client::supprimer(int cin)
{
    bool test=false;
    QSqlQuery query;
    QString cin_string=QString::number(cin);
    query.prepare("Delete from client where cin= :cin");
    query.bindValue(":cin",cin_string);
    test=query.exec();
    return test;
}

QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("SELECT* FROM client");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mail"));


    return model;
}

bool Client::modifier()
{

    bool test=false;
       QSqlQuery query;
       QString cin_string=QString::number(cin);

            query.prepare("UPDATE client SET nom=:nom, prenom=:prenom, adresse=:adresse, mail=:mail where cin=:cin");

            query.bindValue(":cin", cin_string);
            query.bindValue(":nom", nom);
            query.bindValue(":prenom", prenom);
            query.bindValue(":adresse", adresse);
            query.bindValue(":mail", mail);

            test=query.exec();

            return test;

  }

