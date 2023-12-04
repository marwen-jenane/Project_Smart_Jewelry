#include "employee.h"
#include "QString"
#include <QtSql/QSqlQuery>
//#include <QVariant>

Employee::Employee()
{
    id_emp=0;
    nom_emp=" ";
    prenom_emp=" ";
    adresse_emp=" ";
    mail_emp=" ";
    poste_emp=" ";
    salaire_emp=0;
    prime_emp=0;
    nbconge_emp=0;
}

Employee::Employee(int i,QString n,QString p,QString a,QString m,QString s,int ss,int pp,int cg)
{
    this->id_emp=i;
    this->nom_emp=n;
    this->prenom_emp=p;
    this->adresse_emp=a;
    this->mail_emp=m;
    this->poste_emp=s;
    this->salaire_emp=ss;
    this->prime_emp=pp;
    this->nbconge_emp=cg;
}

QString Employee::getNom(){return nom_emp;}
QString Employee::getPrenom(){return prenom_emp;}
QString Employee::getAdresse(){return adresse_emp;}
QString Employee::getMail(){return mail_emp;}
QString Employee::getPoste(){return poste_emp;}
int Employee::getID(){return id_emp;}

int Employee::getSalaire(){return salaire_emp;}
int Employee::getPrime(){return prime_emp;}
int Employee::getConge(){return nbconge_emp;}

void Employee::setNom(QString n){this->nom_emp=n;}
void Employee::setPrenom(QString p){this->prenom_emp=p;}
void Employee::setAdresse(QString a){this->adresse_emp=a;}
void Employee::setMail(QString p){this->mail_emp=p;}
void Employee::setPoste(QString s){this->poste_emp=s;}
void Employee::setId(int id){this->id_emp=id;}
void Employee::setSalaire(int id){this->salaire_emp=id;}
void Employee::setPrime(int id){this->prime_emp=id;}
void Employee::setConge(int id){this->nbconge_emp=id;}

bool Employee::ajouter()
{
    QSqlQuery quer;
    QString ids=QString::number(id_emp);
    QString salaires=QString::number(salaire_emp);
    QString primes=QString::number(prime_emp);
    QString conges=QString::number(nbconge_emp);
    quer.prepare("INSERT INTO employe (id_emp,nom_emp,prenom_emp,adresse_emp,mail_emp,poste_emp,salaire_emp,prime_emp,nbconge_emp) "
                   "VALUES (:id_emp,:nom_emp,:prenom_emp,:adresse_emp,:mail_emp,:poste_emp,:salaire_emp,:prime_emp,:nbconge_emp)");

    quer.bindValue(":id_emp",ids);
    quer.bindValue(":nom_emp", nom_emp);
    quer.bindValue(":prenom_emp", prenom_emp);
    quer.bindValue(":adresse_emp", adresse_emp);
    quer.bindValue(":mail_emp", mail_emp);
    quer.bindValue(":poste_emp", poste_emp);
    quer.bindValue(":salaire_emp", salaires);
    quer.bindValue(":prime_emp", primes);
    quer.bindValue(":nbconge_emp", conges);

    return quer.exec();

}

QSqlQueryModel* Employee::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe order by id_emp");
    model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject:: tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Poste"));
    model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Salaire"));
    model->setHeaderData(7, Qt::Horizontal, QObject:: tr("Note"));
    model->setHeaderData(8, Qt::Horizontal, QObject:: tr("Nb J. Congé"));

    return model;
}

QSqlQueryModel* Employee::rechercher(int id_e)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QString id_s=QString ::number(id_e);
    model->setQuery("SELECT * FROM employe where id_emp="+id_s);
    model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject:: tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Poste"));
    model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Salaire"));
    model->setHeaderData(7, Qt::Horizontal, QObject:: tr("Note"));
    model->setHeaderData(8, Qt::Horizontal, QObject:: tr("Nb J. Congé"));

    return model;
}


QSqlQueryModel* Employee::tri_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe order by id_emp");
    model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject:: tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Poste"));
    model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Salaire"));
    model->setHeaderData(7, Qt::Horizontal, QObject:: tr("Note"));
    model->setHeaderData(8, Qt::Horizontal, QObject:: tr("Nb J. Congé"));

    return model;
}


QSqlQueryModel* Employee::tri_nom()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe order by upper(nom_emp)");
    model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject:: tr("Adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Poste"));
    model->setHeaderData(6, Qt::Horizontal, QObject:: tr("Salaire"));
    model->setHeaderData(7, Qt::Horizontal, QObject:: tr("Note"));
    model->setHeaderData(8, Qt::Horizontal, QObject:: tr("Nb J. Congé"));

    return model;
}
bool Employee::supprimer(int id_e)
{
    QSqlQuery query;
    query.prepare("Delete from employe where id_emp=:id_e" );
    query.bindValue(":id_e",id_e);

    return query.exec();
}


bool Employee::modifier()
{
   QSqlQuery query;
   QString id_string= QString::number(id_emp);
   QString salaires= QString::number(salaire_emp);
   QString primes= QString::number(prime_emp);
   QString conges= QString::number(nbconge_emp);

   query.prepare("UPDATE  employe SET nom_emp=:nom, prenom_emp=:prenom,adresse_emp=:adresse,mail_emp=:mail,poste_emp=:poste,salaire_emp=:ss,prime_emp=:pp,nbconge_emp=:cg WHERE id_emp =:id_e")  ;

   query.bindValue(":id_e",id_string);
   query.bindValue(":nom",nom_emp);
   query.bindValue(":prenom",prenom_emp);
   query.bindValue(":adresse",adresse_emp);
   query.bindValue(":mail",mail_emp);
   query.bindValue(":poste",poste_emp);
   query.bindValue(":ss",salaires);
   query.bindValue(":pp",primes);
   query.bindValue(":cg",conges);
   return query.exec();
}

QSqlQueryModel* Employee::prime()
{


    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT id_emp Id,nom_emp Nom,prenom_emp Prenom,salaire_emp Salaire,prime_emp note,salaire_emp*prime_emp/20 prime FROM employe where prime_emp>=10 ");
    model->setHeaderData(0, Qt::Horizontal, QObject:: tr("Id"),Qt::cyan);
    model->setHeaderData(1, Qt::Horizontal, QObject:: tr("Nom"),Qt::cyan);
    model->setHeaderData(2, Qt::Horizontal, QObject:: tr("Prenom"),Qt::cyan);
    model->setHeaderData(3, Qt::Horizontal, QObject:: tr("Salaire"),Qt::cyan);
    model->setHeaderData(4, Qt::Horizontal, QObject:: tr("Note"));
    model->setHeaderData(5, Qt::Horizontal, QObject:: tr("Prime"));

    return model;
}


bool Employee::reset_prime()
{
   QSqlQuery query;
   query.prepare("UPDATE  employe SET prime_emp= 0")  ;

   return query.exec();
}

bool Employee::conge(int id_e,int cong)
{
   QSqlQuery query;
   QString id_string= QString::number(id_e);

   QString congs= QString::number(cong);

   query.prepare("UPDATE  employe SET nbconge_emp= nbconge_emp  -" + congs + " WHERE id_emp =" +id_string)  ;



   return query.exec();
}

bool Employee::conge_annuel()
{
   QSqlQuery query;
   query.prepare("UPDATE  employe set nbconge_emp=nbconge_emp + 26")  ;

   return query.exec();
}

