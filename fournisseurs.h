#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include <QString.h>
#include <QSqlQueryModel>

#include <QtCharts/QChartView>
#include <QtCharts>

class Fournisseurs
{
private:
    int IDF;
    QString nomF;
    QString nom_entreprise;
    QString adresse;
    QString email;
    int num;
    //QString test;

public:
    Fournisseurs();
    Fournisseurs(int,QString,QString,QString,QString,int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    bool idExists(const int &ID);

    QSqlQueryModel* rechercher(QString recherche);
    QSqlQueryModel * triFournisseur(QString tri);
    QVector<int> statFournisseur();

   /* void saveAjoutFournisseur();
    QString loadFournisseur();
    void saveUpdateFournisseur(QString Nom, QString nomEntreprise, QString Adresse, QString Email, int Numero);
    void saveDeleteFournisseur();
*/
    QMap<QString, int> getFournisseur_Statistics();

    int adresse_calcul(QString adr);
    int adresse_calcul_total(QString adr);


    int getIDF();
    QString getnomF();
    QString getnom_entreprise();
    QString getadresse();
    QString getemail();
    int getnum();

    void setIDF(int);
    void setnomF(QString);
    void setnom_entreprise(QString);
    void setadresse(QString);
    void setemail(QString);
    void setnum(int);
};

#endif // FOURNISSEURS_H
