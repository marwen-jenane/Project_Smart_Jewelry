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

   /* static void saveAjoutFournisseur(int ID, const QString& nomF, const QString& nom_entreprise,
                                         const QString& adresse, const QString& email, int num);
       static void saveUpdateFournisseur(const QString& oldNomF, const QString& oldNomEntreprise,
                                          const QString& oldAdresse, const QString& oldEmail, int oldNum,
                                          const QString& newNomF, const QString& newNomEntreprise,
                                          const QString& newAdresse, const QString& newEmail, int newNum);*/

    void saveAjoutFournisseur();
        QString loadFournisseur();
        void saveUpdateFournisseur(QString Nom, QString nomEntreprise, QString Adresse, QString Email, int Numero);
        void saveDeleteFournisseur();
        void saveBeforeUpdateFournisseur();
};

#endif // HISTORIQUE_H
