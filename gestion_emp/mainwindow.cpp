#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDate>
#include<QPdfWriter>
#include<QPainter>
#include<QTextStream>
#include<QSqlQuery>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->l_id->setValidator(new QIntValidator(0,99999999,this));
    ui->tab_emp->setModel(emp.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_b_ajouter_clicked()
{
    int id_emp= ui->l_id->text().toInt();
    int salaire_emp=ui->le_salaire->text().toInt();
    int prime_emp=ui->le_prime->text().toInt();
    int nbconge_emp=ui->le_conge->text().toInt();
    QString nom_emp= ui->l_nom->text();
    QString prenom_emp= ui->l_prenom->text();
    QString adresse_emp=ui->l_adresse->text();
    QString mail_emp=ui->l_mail->text();
    QString poste_emp=ui->l_poste->text();

    Employee Emp(id_emp,nom_emp,prenom_emp,adresse_emp,mail_emp,poste_emp,salaire_emp,prime_emp,nbconge_emp);
    bool test=Emp.ajouter();
    QMessageBox msgbox;
    if  (test)
        msgbox.setText("Ajout avec succès");
    else
        msgbox.setText("Echec d'ajout");
    msgbox.exec();
}

void MainWindow::on_b_supp_clicked()
{
    Employee emp;
    emp.setId(ui->le_sup->text().toInt());
    bool test=emp.supprimer(emp.getID());
    QMessageBox msBox;
    if(test)
        msBox.setText("suppression avec succes.");
    else
        msBox.setText("Echec de suppression");
    msBox.exec();
}


void MainWindow::on_b_supprimer_clicked()
{
    Employee emp;
    emp.setId(ui->le_sup->text().toInt());
    bool test=emp.supprimer(emp.getID());
    QMessageBox msBox;
    if(test)
        msBox.setText("suppression avec succes.");
    else
        msBox.setText("Echec de suppression");
    msBox.exec();
}

void MainWindow::on_b_afficher_clicked()
{
    Employee emp;
    ui->tab_emp->setModel(emp.afficher());
}


void MainWindow::on_b_modifier_clicked()
{
    QString nom= ui->le_nom->text();
    QString prenom= ui->le_prenom->text();
    QString adresse= ui->le_adresse->text();
    QString mail= ui->le_mail->text();
    QString poste= ui->le_poste->text();

    int id_e=ui->le_id->text().toInt();
    int salaire=ui->l_salaire->text().toInt();
    int prime=ui->l_prime->text().toInt();
    int conge=ui->l_conge->text().toInt();
    Employee emp(id_e,nom,prenom,adresse,mail,poste,salaire,prime,conge);
    bool test=emp.modifier();
    QMessageBox msgbox;
    if(test)
       msgbox.setText("Modification avec succes.");
    else
       msgbox.setText("Echec de Modification");
    msgbox.exec();
}


void MainWindow::on_b_rechercher_clicked()
{
    int id=ui->le_recherche->text().toInt();
    ui->tableView->setModel(emp.rechercher(id));

}

void MainWindow::on_b_tri_emp_clicked()
{
    ui->tableView_tri->setModel(emp.tri_id());
}

void MainWindow::on_b_tri_nom_clicked()
{
    ui->tableView_tri->setModel(emp.tri_nom());
}



void MainWindow::on_pb_prime_clicked()
{
    ui->tv_prime->setModel(emp.prime());

}



void MainWindow::on_b_reset_prime_clicked()
{
    bool test=emp.reset_prime();
    QMessageBox msgbox;
    if (test)
        msgbox.setText("Les notes de Rendement sont à zéro ");
    else
        msgbox.setText("Echec de Reset Prime");
    msgbox.exec();
}

void MainWindow::on_b_conge_clicked()
{
    int id_e=ui->lc_conge->text().toInt();
    int conge=ui->lc_congea->text().toInt();
    bool test=emp.conge(id_e,conge);
    QMessageBox msgbox;
    if (test)
        msgbox.setText("Nouveau solde de congé validé avec succès ....");
    else
        msgbox.setText("Echec de validation de congé");
    msgbox.exec();
}

void MainWindow::on_b_congea_clicked()
{

    bool test=emp.conge_annuel();

    QMessageBox msgbox;
    if (test)
        msgbox.setText("Solde de congé annuel ajouté à tout le personnel avec succès ... ");
    else
        msgbox.setText("Echec d'attribution du solde annuel");
    msgbox.exec();

}

void MainWindow::on_pb_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/DELL/Desktop/employe.pdf");
    QPainter painter(&pdf);
    QString strStream;
    QTextStream out(&strStream);
    int i = 4000;
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Times New Roman", 25));
    painter.drawText(3000,1400,"Liste des Employés");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Times New Roman", 7));

    painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3000,9400,500);

    painter.drawText(300,3300,"ID Employé ");
    painter.drawText(1300,3300,"Nom Employé");
    painter.drawText(2300,3300,"Prénom Employé");
    painter.drawText(3300,3300,"Adresse Employé ");
    painter.drawText(4300,3300,"Mail Employé");
    painter.drawText(5300,3300,"Poste Employé ");
    painter.drawText(6300,3300,"Salaire");
    painter.drawText(7300,3300,"Note");
    painter.drawText(8300,3300,"Congé");

    painter.drawRect(100,3000,9400,9000);
    QSqlQuery query;
    query.prepare("select * from EMPLOYE order by id_emp");
    query.exec();
    while (query.next())
    {
           painter.drawText(300,i,query.value(0).toString());
           painter.drawText(1300,i,query.value(1).toString());
           painter.drawText(2300,i,query.value(2).toString());
           painter.drawText(3300,i,query.value(3).toString());
           painter.drawText(4300,i,query.value(4).toString());
           painter.drawText(5300,i,query.value(5).toString());
           painter.drawText(6300,i,query.value(6).toString());
           painter.drawText(7300,i,query.value(7).toString());
           painter.drawText(8300,i,query.value(8).toString());
           i = i + 350;
    }
    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),QObject::tr("PDF Enregistré!.\n" "Click Ok to exit."), QMessageBox::Cancel);
}



void MainWindow::on_le_du_userDateChanged(const QDate &date)
{
}

void MainWindow::on_pushButton_clicked()
{

    int nbji20;
    int nbjs20;
    int nbjtot;

    QtCharts::QBarSet *set0 = new QtCharts::QBarSet("inférieur à 20");

    QtCharts::QBarSet *set1 = new QtCharts::QBarSet("supérieur à 20 ");

    QSqlQuery query("select count(*) from employe where nbconge_emp<20");
    while (query.next())
    {
        nbji20 = query.value(0).toInt();
    }
    QSqlQuery query1("select count(*) from employe where nbconge_emp>=20");
    while (query1.next())
    {
        nbjs20 = query1.value(0).toInt();
    }
    nbjtot = nbji20+nbjs20;

    * set0 << nbji20<<nbjtot ;

    * set1 << nbjs20<<nbjtot  ;

    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();

    series->append(set0);

    series->append(set1);

    QtCharts::QChart *chart = new QtCharts::QChart();

    chart->addSeries(series);

    chart->setTitle("Nbre de personnel ayant nbre de Jours de Congé  inférieur à 20 ou supérieur ou égal à20");

    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    chart->resize(650,600);


    QStringList categories;

    categories << " Congé des employés" ;


    QtCharts::QBarCategoryAxis *axis = new QtCharts::QBarCategoryAxis();

    axis->append(categories);

    chart->createDefaultAxes();

    chart->setAxisX(axis,series);
    chart->legend()->setVisible(true);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);

    chartView->show();


}

void MainWindow::on_led_clicked()
{

}
