#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>

#include <QtSql/QSqlQueryModel>



class Employee
{
private:
    QString nom_emp,prenom_emp,adresse_emp,mail_emp,poste_emp;
    int id_emp,salaire_emp,prime_emp,nbconge_emp;
public:
    Employee();
    Employee(int,QString,QString,QString,QString,QString,int,int,int);

    QString getNom();
    QString getPrenom();
    QString getAdresse();
    QString getMail();
    QString getPoste();
    int getID();
    int getSalaire();
    int getPrime();
    int getConge();


    void setNom(QString n);
    void setPrenom(QString p);
    void setAdresse(QString a);
    void setMail(QString p);
    void setPoste(QString s);
    void setId(int id);
    void setSalaire(int id);
    void setPrime(int id);
    void setConge(int id);

    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(int);
    QSqlQueryModel* tri_id();
    QSqlQueryModel* tri_nom();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* prime();
    bool reset_prime();
    bool conge(int,int);
    bool conge_annuel();
};

#endif // EMPLOYEE_H
