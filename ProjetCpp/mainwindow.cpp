#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stock.h"
#include <QMessageBox>
#include <QTabWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_stock->setModel(s.afficher());
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Ajouter_clicked()
{
    int id=ui->idajout->text().toInt();
    QString type=ui->typeajout->text();
    int quantite=ui->quantiteajout->text().toInt();
    float prix=ui->prixajout->text().toInt();
    stock s(id,quantite,prix,type);
bool test;
test=s.ajouter();
if(test)
{
    QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("Ajout effectue\n"
                                         "click cancel to exit."), QMessageBox::Cancel);
}
else
    QMessageBox::critical(nullptr, QObject::tr("not OK"),
                          QObject::tr("Ajout non effectue.\n"
                                      "click cancel to exit."), QMessageBox::Cancel);
    ui->tab_stock->setModel(s.afficher());

}


void MainWindow::on_Supp_clicked()
{
    int ID = ui->IDsupp->text().toInt();
    stock stock;
    bool test=stock.supprimer(ID);
        if(test)
        {
           QMessageBox::information(nullptr, QObject::tr("database is open"),
             QObject::tr("suppression successful.\n"
             "Click Cancel to exit."), QMessageBox::Cancel);
         }
        else
         {
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
            QObject::tr("suppression failed.\n"
            "Click Cancel to exit."), QMessageBox::Cancel);
         }
        ui->tab_stock->setModel(s.afficher());
         ui->IDsupp->clear();
}

void MainWindow::on_modifier_clicked()
{
    int id=ui->idajout->text().toInt();
    int prix=ui->prixajout->text().toInt();
    int quantite=ui->quantiteajout->text().toInt();
    QString type=ui->typeajout->text();
    stock s(id,quantite,prix,type);

                bool test=s.modifier(id);
                if(test)
                {
                    QMessageBox::information(nullptr, QObject::tr("OK"),
                                QObject::tr("Update effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
                    ui->tab_stock->setModel(s.afficher());
                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                QObject::tr("Update non effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
}
