#include "fournisseurs.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QFile>
#include <QDateTime>



Fournisseurs::Fournisseurs()
{
     IDF=0;
     nomF="";
     nom_entreprise="";
     adresse="";
     email="";
     num=0;
}

Fournisseurs::Fournisseurs(int IDF, QString nomF, QString nom_entreprise, QString adresse, QString email,int num)
{
    this->IDF=IDF ;
    this->nomF=nomF ;
    this->nom_entreprise=nom_entreprise ;
    this->adresse=adresse ;
    this->email=email ;
   this->num=num ;

}

int Fournisseurs::getIDF() {return IDF;}
QString Fournisseurs::getnomF() {return nomF;}
QString Fournisseurs::getnom_entreprise() {return nom_entreprise;}
QString Fournisseurs::getadresse() {return adresse;}
QString Fournisseurs::getemail() {return email;}
int Fournisseurs::getnum() {return num;}

void Fournisseurs::setIDF(int ID){this->IDF=ID;}
void Fournisseurs::setnomF(QString nomF){this->nomF=nomF;}
void Fournisseurs::setnom_entreprise(QString nom_entreprise){this->nom_entreprise=nom_entreprise;}
void Fournisseurs::setadresse(QString adresse){this->adresse=adresse;}
void Fournisseurs::setemail(QString email){this->email=email;}
void Fournisseurs::setnum(int num){this->num=num;}

bool Fournisseurs::ajouter()
{
    bool test=false;
    QSqlQuery query;
    QString IDF_string= QString::number(IDF);
    QString num_string= QString::number(num);
          query.prepare("INSERT INTO GS_FOURNISSEURS (IDF, NOMF, NOM_ENTREPRISE, ADRESSE, EMAIL, NUM) "
                        "VALUES (:IDF, :NOMF, :NOM_ENTREPRISE, :ADRESSE, :EMAIL, :NUM)");
          query.bindValue(":IDF",IDF_string);
          query.bindValue(":NOMF",nomF);
          query.bindValue(":NOM_ENTREPRISE",nom_entreprise);
          query.bindValue(":ADRESSE",adresse);
          query.bindValue(":EMAIL",email);
          query.bindValue(":NUM",num_string);

         return query.exec();
}
bool Fournisseurs::supprimer(int IDF)
{
    QSqlQuery query;
          query.prepare("Delete FROM GS_FOURNISSEURS where IDF=:IDF");
          query.bindValue(0, IDF);

         return query.exec();
}

QSqlQueryModel* Fournisseurs::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

      model->setQuery("SELECT* FROM GS_FOURNISSEURS");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom Fournisseur"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom d'entreprise"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("Numero"));
  return model;
}


bool Fournisseurs::modifier(){

      QSqlQuery query;
          QString IDF_string=QString::number(IDF);
           QString num_string= QString::number(num);

            query.prepare("UPDATE GS_FOURNISSEURS SET NOMF=:nomF, NOM_ENTREPRISE=:nom_entreprise , ADRESSE=:adresse , EMAIL=:email, NUM=:num  where IDF=:IDF ");

            query.bindValue(":IDF", IDF_string);
            query.bindValue(":nomF", nomF);
            query.bindValue(":nom_entreprise", nom_entreprise);
            query.bindValue(":adresse",adresse);
            query.bindValue(":email", email);
            query.bindValue(":num", num_string);


              return query.exec();

  }



/*******Contorle saisir de l'existance de ID***********/

bool Fournisseurs::idExists(const int &IDF)
{
    QSqlQuery query;
    query.prepare("SELECT IDF FROM GS_FOURNISSEURS WHERE IDF=:IDF");
    query.bindValue(":IDF", IDF);

    if (query.exec() && query.next())
    {
        // If a row is fetched, the ID exists in the database.
        return true;
    }

    // If no rows were fetched, the ID does not exist.
    return false;
}

QSqlQueryModel * Fournisseurs::rechercher(QString recherche)
            {
                QSqlQueryModel * model = new QSqlQueryModel();
                model->setQuery("SELECT * from GS_FOURNISSEURS WHERE IDF LIKE ('%"+recherche+"%') OR UPPER(NOMF) LIKE UPPER('%"+recherche+"%') OR UPPER(NOM_ENTREPRISE) LIKE UPPER('%"+recherche+"%')");

                model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
                model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom Fournisseur"));
                model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom d'entreprise"));
                model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse"));
                model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
                model->setHeaderData(5, Qt::Horizontal, QObject::tr("Numero"));
                return model;

            }

QSqlQueryModel * Fournisseurs::triFournisseur(QString tri)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    if(tri == "par defaut"){
        model->setQuery("SELECT * FROM GS_FOURNISSEURS ");
    }
    else if (tri == "ID")
    {
        model->setQuery("SELECT * FROM GS_FOURNISSEURS ORDER BY IDF");
    }
    else if (tri == "nom")
    {
        model->setQuery("SELECT * FROM GS_FOURNISSEURS ORDER BY nomF");
    }
    else if (tri == "nom_entreprise")
        {
            model->setQuery("SELECT * FROM GS_FOURNISSEURS ORDER BY nom_entreprise");
        }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nomF"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom_entreprise"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("num"));
    return model;
}



QMap<QString, int> Fournisseurs::getFournisseur_Statistics()
{
        QMap<QString, int> statistics;

        // Query for GS_FOURNISSEURS with num < 50
        QSqlQuery query1;
        query1.prepare("SELECT COUNT(*) AS count FROM GS_FOURNISSEURS WHERE adresse=:tunis ");
        query1.bindValue(":tunis", "tunis");
       // If the query is successful, move to the first (and only) result row.
        if (query1.exec())
        {
            query1.next();
            statistics["tunis"] = query1.value("count").toInt();
        }
        else
        {
            qDebug() << "Error in query (tunis):" << query1.lastError().text();
        }

        // Query for GS_FOURNISSEURS with num between 50 and 100
       /* QSqlQuery query2;
        query2.prepare("SELECT COUNT(*) AS count FROM GS_FOURNISSEURS WHERE adresse=:sfax ");
        query2.bindValue(":sfax", "sfax");
        if (query2.exec())
        {
            query2.next();
            statistics["sousse"] = query2.value("count").toInt();
        }
        else
        {
            qDebug() << "Error in query (sousse):" << query2.lastError().text();
        }*/
            
            QSqlQuery query3;
            query3.prepare("SELECT COUNT(*) AS count FROM GS_FOURNISSEURS WHERE adresse=:ariana ");
            query3.bindValue(":ariana", "ariana");
            if (query3.exec())
            {
                query3.next();
                statistics["ariana"] = query3.value("count").toInt();
            }
            else
            {
                qDebug() << "Error in query (ariana):" << query3.lastError().text();
            }

                QSqlQuery query4;
                query4.prepare("SELECT COUNT(*) AS count FROM GS_FOURNISSEURS WHERE adresse=:gabes ");
                query4.bindValue(":gabes", "gabes");
                if (query4.exec())
                {
                    query4.next();
                    statistics["gabes"] = query4.value("count").toInt();
                }
                else
                {
                    qDebug() << "Error in query (gabes):" << query4.lastError().text();
                }

                QSqlQuery query5;
                query5.prepare("SELECT COUNT(*) AS count FROM GS_FOURNISSEURS WHERE adresse=:beja ");
                query5.bindValue(":beja", "beja");
                if (query5.exec())
                {
                    query5.next();
                    statistics["beja"] = query5.value("count").toInt();
                }
                else
                {
                    qDebug() << "Error in query (beja):" << query5.lastError().text();
                }

        return statistics;
}
