#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include<QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_cin->setValidator(new QIntValidator(100, 99999999, this));
    ui->tab_clients->setModel(c1.afficher());
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int cin=ui->le_cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString adresse=ui->l_adresse->text();
    QString mail=ui->le_mail->text();
    Client c(cin,nom,prenom,adresse,mail);
    bool test=c.ajouter();


    if(test)
    {
    QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_clients->setModel(c1.afficher());
}
else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Ajout non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_2_clicked()
{
    //Client c1;
    int cin=ui->le_cins->text().toInt();
    //c1.setcin(ui->le_cins->text().toInt());
    //bool test=c1.supprimer(c1.getcin());
    bool test=c1.supprimer(cin);

    if(test)
    {
    QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Suppression effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_clients->setModel(c1.afficher());
}
else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Suppression non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_3_clicked()
{
    int cin=ui->le_cin2->text().toInt();
    QString nom=ui->le_nom2->text();
    QString prenom=ui->le_prenom2->text();
    QString adresse=ui->l_adresse2->text();
    QString mail=ui->le_mail2->text();
    Client c(cin,nom,prenom,adresse,mail);
    bool test=c.modifier();

    if(test)
    {
    QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Mdification effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_clients->setModel(c1.afficher());
}
else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Modification non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
