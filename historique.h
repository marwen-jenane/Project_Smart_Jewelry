#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <QString.h>

class historique
{
private:
    int ID_H;
    QString nomH;
    QString nom_entrepriseH;
    QString adresseH;
    QString emailH;
    int numH;

public:
    historique();
    historique(int ID_H,QString nomH,QString nom_entrepriseH,QString adresseH,QString emailH,int numH);

    void saveAjoutFournisseur();
       // QString loadFournisseur();
        void saveUpdateFournisseur(QString Nom, QString nomEntreprise, QString Adresse, QString Email, int Numero);
        void saveDeleteFournisseur();
        void saveBeforeUpdateFournisseur();
};

#endif // HISTORIQUE_H
