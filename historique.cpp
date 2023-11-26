#include "historique.h"
#include <QFile>
#include <QDateTime>
#include <QSqlQuery>
#include "fournisseurs.h"
#include <QTextStream>


historique::historique()
{

}

historique::historique(int ID_H,QString nomH,QString nom_entrepriseH,QString adresseH,QString emailH,int numH)
{
     this->ID_H=ID_H;
     this->nomH=nomH;
     this-> nom_entrepriseH=nom_entrepriseH;
     this->adresseH=adresseH;
     this->emailH=emailH;
     this->numH=numH;
}

void historique::saveAjoutFournisseur(){
    QFile file ("C:/Users/user/Documents/Interface_Four/historique.txt");
    if (!file.open(QIODevice::WriteOnly|  QIODevice::Append | QIODevice::Text))
        return;
    QSqlQuery query;
         QString num_string= QString::number(numH);
    // Create a QTextStream object associated with the file for easy text output.
    QTextStream out(&file);
    out.setCodec("UTF-8");
    QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
    out << "\n""*****************************************Ajouter********************************";
    out << "\n nomF: "+nomH + ", nom_entreprise: " +nom_entrepriseH+ ", adresse: " +adresseH+ ", email: " +emailH+ ", num: " +num_string<< "\n" "un nouveau fournisseur a été ajouter le " +sDate << "\n";
}

void historique::saveUpdateFournisseur(QString Nom, QString nomEntreprise, QString Adresse, QString Email, int numero)
{
    QFile file ("C:/Users/user/Documents/Interface_Four/historique.txt");
    if (!file.open(QIODevice::WriteOnly|  QIODevice::Append | QIODevice::Text))
        return;
    QSqlQuery query;
         //QString num_string= QString::number(numH);
         QString numero_string= QString::number(numero);

    QTextStream out(&file);
    out.setCodec("UTF-8");
    QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
    out << "\n""*****************************************Update********************************";
    //out << "\n nomF: "+nomH + ", nom_entreprise: " +nom_entrepriseH + ", adresse: " +adresseH+ ", email: " +emailH+ ", num: " +num_string;
    out << "\n Nom: "+Nom + ", nomEntreprise: " +nomEntreprise+ ", Adresse: " +Adresse+ ", Email: " +Email +", Numero: " +numero_string<< "\n" "Cet fournisseur a été modifié le " +sDate << "\n";
}


void historique::saveDeleteFournisseur(){
    QFile file ("C:/Users/user/Documents/Interface_Four/historique.txt");
    if (!file.open(QIODevice::WriteOnly|  QIODevice::Append | QIODevice::Text))
        return;

    QSqlQuery query;
         QString num_string= QString::number(numH);
         QString ID_H_string= QString::number(ID_H);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz");
    out << "\n""*****************************************Delete********************************";
    out <<  "\n nomF: "+nomH + ", nom_entreprise: " +nom_entrepriseH+ ", adresse: " +adresseH+ ", email: " +emailH+ ", num: " +num_string<< "\n" "Cet fournisseur a été supprimé le " +sDate << "\n";
    out << "   \n ID:   "+ID_H_string << "\n" "Cet fournisseur a été supprimé le " +sDate << "\n";
}
