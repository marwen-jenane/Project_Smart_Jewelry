#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseurs.h"
#include "historique.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>

#include <QTextDocument>
#include <QTextStream>
#include <QDate>
#include <QPrinter>
#include <QPainter>

#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QStandardPaths>
#include<QPdfWriter>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QHBoxLayout>
#include <QtCharts/QLegend>
#include <QtCharts/QHorizontalStackedBarSeries>

#include <QTextDocument>
#include <QTextStream>
#include <QDate>
#include <QPrinter>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QStandardPaths>
#include<QPdfWriter>
#include <QLayout>
#include <QVector>
#include <QStringList>
#include <QPalette>
#include <QApplication>
#include <QBarset>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts>
#include <QPieSlice>
#include <QTimer>
using namespace QtCharts;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_IDF->setValidator(new QIntValidator(0, 99999999, this));
    ui->tab_Fournisseur->setModel(F.afficher());
   // ui->comboBox->setModel(F.afficher());
    FournisseurStatisticsChartView = nullptr;


    int ret=myArduino.connect_arduino();
                  // lancer la connexion à arduino
                 switch(ret){
                 case(0):qDebug()<< "arduino is available and connected to : "<< myArduino.getarduino_port_name();
                     break;
                 case(1):qDebug() << "arduino is available but not connected to :" <<myArduino.getarduino_port_name();
                    break;
                 case(-1):qDebug() << "arduino is not available";
                 }

               //  QObject::connect(myArduino.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

                 timer = new QTimer(this);
                      connect(timer, &QTimer::timeout, this, &MainWindow::loop);
                      timer->start(5000);  // Démarrer le temporisa

                      ui->le_IDF->setValidator(new QIntValidator(0, 99999999, this));
                      ui->tab_Fournisseur->setModel(F.afficher());
                     // ui->comboBox->setModel(F.afficher());
                      FournisseurStatisticsChartView = nullptr;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{


    int ID=ui->le_IDF->text().toInt();
    QString nomF=ui->le_nomF->text();
    QString nom_entreprise=ui->le_nomEntreprise->text();
    QString adresse=ui->le_adresseF->text();
    QString email=ui->le_emailF->text();
    int num=ui->le_numeroF->text().toInt();
    Fournisseurs F ( ID,  nomF,  nom_entreprise,  adresse, email, num);
    historique H( ID,  nomF,  nom_entreprise,  adresse, email, num);
    bool test=F.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
             ui->tab_Fournisseur->setModel(F.afficher());
             N.NotificationAjouterFournisseur();
             H.saveAjoutFournisseur();

     }
     else
    {
         QMessageBox::critical(nullptr, QObject::tr("FAILED"),
                     QObject::tr("Ajout failed.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     }
    ui->le_IDF->clear();
    ui->le_nomF->clear();
    ui->le_nomEntreprise->clear();
    ui->le_adresseF->clear();
    ui->le_emailF->clear();
    ui->le_numeroF->clear();
}



void MainWindow::on_pb_supprimer_clicked()
{
    int id_a_supp = ui->le_id_supp->text().toInt();
    QString id_text =ui->le_id_supp->text();

    if (id_text.isEmpty()) {
        // Show an error message if the ID input is empty.
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Veuillez entrer un identifiant avant de tenter de supprimer."), QMessageBox::Ok);
        return;
    }

    // Check if the ID exists in the database.
    Fournisseurs F1;
    historique H(id_a_supp,F1.getnomF(),F1.getnom_entreprise(),F1.getadresse(),F1.getemail(),F1.getnum());
    F1.setIDF(id_a_supp);

    if (F1.idExists(id_a_supp))
    {
        // The ID exists, so proceed with the deletion.
        bool test = F1.supprimer(F1.getIDF());

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Suppression avec succès.\nClick Cancel to exit."), QMessageBox::Cancel);
            ui->tab_Fournisseur->setModel(F.afficher()); // Mise à jour
             N.NotificationSupprimerFournisseur();
             H.saveDeleteFournisseur();
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("La suppression a échoué.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }
    else {
        // Show an error message if the ID does not exist in the database and return from the function.
        QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("L'identifiant n'existe pas."), QMessageBox::Ok);
        return;
    }
}


void MainWindow::on_pb_miseajour_clicked()
{
   int IDF=ui->le_IDF->text().toInt();
    QString nomF=ui->le_nomF->text();
    QString nom_entreprise=ui->le_nomEntreprise->text();
    QString adresse=ui->le_adresseF->text();
    QString email=ui->le_emailF->text();
    int num=ui->le_numeroF->text().toInt();

    Fournisseurs F ( IDF,  nomF,  nom_entreprise,  adresse,  email, num);
    historique H(F.getIDF(),F.getnomF(),F.getnom_entreprise(),F.getadresse(),F.getemail(),F.getnum());

    bool test=F.modifier();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("mise à jour successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_Fournisseur->setModel(F.afficher());
            N.NotificationModifierFournisseur();
            H.saveUpdateFournisseur(nomF,  nom_entreprise,  adresse,  email, num);

     }
     else
    {
         QMessageBox::critical(nullptr, QObject::tr("FAILED"),
                     QObject::tr("mise à jour failed.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ui->le_IDF->clear();
    ui->le_nomF->clear();
    ui->le_nomEntreprise->clear();
    ui->le_adresseF->clear();
    ui->le_emailF->clear();
    ui->le_numeroF->clear();
}

void MainWindow::on_pb_clear_clicked()
{
    // Effacez les champs d'entrée ou effectuez toute autre action que vous souhaitez

}

void MainWindow::on_tab_Fournisseur_activated(const QModelIndex &index)
{
    int i;
i=index.row();
// Create a new QModelIndex for the first column of the same row.
QModelIndex in=index.sibling(i,0);

// Retrieve the data from the model for the specified index.
QString val=ui->tab_Fournisseur->model()->data(in).toString();

    QSqlQuery qry;
    qry.prepare("select IDF,nomF,nom_entreprise,adresse,email,num from GS_FOURNISSEURS where IDF='"+val+"' " );


    if(qry.exec())
    {
        while(qry.next())
        {
            ui->le_IDF->setText(qry.value(0).toString());
            ui->le_nomF->setText(qry.value(1).toString());
            ui->le_nomEntreprise->setText(qry.value(2).toString());
            ui->le_adresseF->setText(qry.value(3).toString());
            ui->le_emailF->setText(qry.value(4).toString());
            ui->le_numeroF->setText(qry.value(5).toString());
        }
    }
}


void MainWindow::on_x_recherche_textChanged(const QString &arg1)
{
        if(arg1!="")
            ui->tab_Fournisseur->setModel(F.rechercher(arg1));
            else
                ui->tab_Fournisseur->setModel(F.rechercher(arg1));
}

void MainWindow::on_comboBox_tri_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "par defaut")
        {
           ui->tab_Fournisseur->setModel(F.triFournisseur(arg1));
        }
        else if(arg1 == "ID")
        {
            ui->tab_Fournisseur->setModel(F.triFournisseur(arg1));
        }
        else if(arg1 == "nomF")
        {
            ui->tab_Fournisseur->setModel(F.triFournisseur(arg1));
        }
        else
        {
            ui->tab_Fournisseur->setModel(F.triFournisseur(arg1));
        }
}

void MainWindow::on_pb_PDF_clicked()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
            filePath = QDir(filePath).filePath("Interface_Four/listeFournisseurs.pdf");
            QPdfWriter pdf(filePath);

               QPainter painter(&pdf);
               int i = 4100;

                      QColor dateColor(0x4a5bcf);
                      painter.setPen(dateColor);

                      painter.setFont(QFont("Montserrat SemiBold", 11));
                      QDate cd = QDate::currentDate();
                      painter.drawText(8400,250,cd.toString("Tunis"));
                      painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

                      QColor titleColor(0x341763);
                      painter.setPen(titleColor);
                      painter.setFont(QFont("Montserrat SemiBold", 25));

                      painter.drawText(3000,2700,"Liste des fournisseurs");

                      painter.setPen(Qt::black);
                      painter.setFont(QFont("Time New Roman", 15));
                      //painter.drawRect(100,100,9400,2500);
                      painter.drawRect(100,3300,9400,500);

                      painter.setFont(QFont("Montserrat SemiBold", 10));

                      painter.drawText(400,3600,"IDF");
                      painter.drawText(1500,3600,"nomF");
                      painter.drawText(2700,3600,"nom_entreprise");
                      painter.drawText(4100,3600,"adresse");
                      painter.drawText(5400,3600,"email");
                      painter.drawText(6600,3600,"num");
                      painter.setFont(QFont("Montserrat", 10));
                      painter.drawRect(100,3300,9400,9000);

                      QSqlQuery query;
                      query.prepare("select * from GS_FOURNISSEURS");
                      query.exec();
                      int y=4300;
                      while (query.next())
                      {
                          painter.drawLine(100,y,9490,y);
                          y+=500;
                          painter.drawText(400,i,query.value(0).toString());
                          painter.drawText(1500,i,query.value(1).toString());
                          painter.drawText(2700,i,query.value(2).toString());
                          painter.drawText(4100,i,query.value(3).toString());
                          painter.drawText(5400,i,query.value(4).toString());
                          painter.drawText(6600,i,query.value(5).toString());

                         i = i + 500;
                      }
                      QMessageBox::information(nullptr,QObject::tr("Pdf created"),
                      QObject::tr("File created with seccess.\n"
                                  ""),QMessageBox::Ok);
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    int statisticsTabIndex = ui->tabWidget->indexOf(ui->stat);

    // Check if the clicked tab is the "stat" tab.
    if (index == statisticsTabIndex) {
        // If the clicked tab is the "stat" tab, update the Fournisseur statistics chart.
        update_Fournisseur_StatisticsChart();
    } else {
       // clearFournisseur_StatisticsChart();
    }
}


void MainWindow::update_Fournisseur_StatisticsChart()
{
    qDebug() << "Updating Fournisseurs Statistics Chart";
    // Retrieve statistics about Fournisseurs from the F object.
    QMap<QString, int> statistics = F.getFournisseur_Statistics();
    int totalFournisseurs = 0;
    // Calculate the total number of Fournisseurs based on the retrieved statistics.
    for (const int &count : statistics.values()) {
        totalFournisseurs += count;
    }
    // Create a new QPieSeries to represent the data in the pie chart.
    QPieSeries *series = new QPieSeries();

    // Define colors for the pie chart slices.
    QStringList colors = {"#55AA00",  "#005500","#0000FF", "#800080"};
    int colorIndex = 0;

    // Iterate over the statistics and add slices to the pie chart.
    for (const QString &group : statistics.keys()) {
        int count = statistics[group];
        QPieSlice *slice = series->append(group, count);

         // Set the label for each slice with the percentage of the total.
        slice->setLabel(group + ":\n " + QString::number(static_cast<double>(count) / totalFournisseurs * 100, 'f', 2) + "%");

        // Set the color for each slice
        if (colorIndex < colors.size()) {
            slice->setBrush(QColor(colors[colorIndex]));
        } else {
            slice->setBrush(QColor(Qt::green));
        }

        colorIndex++;
    }

  // clearFournisseur_StatisticsChart();

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition par adresse ");
    chart->setBackgroundBrush(QBrush(QColor("#F5F5DC")));
    chart->setAnimationOptions(QChart:: SeriesAnimations);

    FournisseurStatisticsChartView = new QChartView(chart);
    FournisseurStatisticsChartView->setRenderHint(QPainter::Antialiasing);
    FournisseurStatisticsChartView->setParent(ui->stat);
    FournisseurStatisticsChartView->setGeometry(70, 50, 600, 400);

    FournisseurStatisticsChartView->show();
}

void MainWindow::clearFournisseur_StatisticsChart()
{
    // Check if the FournisseurStatisticsChartView is not null
    if (FournisseurStatisticsChartView) {
        delete FournisseurStatisticsChartView;
        FournisseurStatisticsChartView = nullptr;
    }
}



//********************Arduino**************************


void MainWindow::loop() {
    QByteArray data = myArduino.read_from_arduino();

    // Nettoyer les caractères spéciaux "\r\n" de la chaîne
    data = data.trimmed();

    // Convertir les données nettoyées en int (ide)
    bool conversionOk;
    int UID = data.toInt(&conversionOk);

    if (conversionOk) {
        qDebug() << "ID Arduino converti avec succès : " << UID;

        // Exécuter la requête SQL pour vérifier si le ID existe dans la table fournisseur
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT NOMF FROM GS_FOURNISSEURS WHERE IDF = :UID");
        checkQuery.bindValue(":UID", UID);

        if (checkQuery.exec() && checkQuery.next()) {
            // La correspondance a été trouvée, récupérer le nom correspondant
            QString nom = checkQuery.value(0).toString();

            // Envoyer le nom à l'Arduino
            QByteArray response = nom.toUtf8();
            int writeResult = myArduino.write_to_arduino(response);

            if (writeResult == 1) {
                qDebug() << "IDE trouvé, nom envoyé à l'Arduino : " << nom;

                QMessageBox::information(nullptr, QObject::tr("OK"),
                                         QObject::tr("IDE trouvé, nom envoyé à l'Arduino."
                                                     "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
            } else {
                qDebug() << "Échec de l'envoi du nom à l'Arduino.";
            }
        } else {
            // Aucune correspondance trouvée, envoyer une réponse vide à l'Arduino
            QByteArray emptyResponse = "0";
            int writeResult = myArduino.write_to_arduino(emptyResponse);

            if (writeResult == 1) {
                qDebug() << "Aucune correspondance trouvée, réponse vide envoyée à l'Arduino.";
            } else {
                qDebug() << "Échec de l'envoi de la réponse vide à l'Arduino.";
            }
        }
    } else {
        // La conversion en int a échoué
        qDebug() << "Échec de la conversion du matricule Arduino en entier.";
        // Traitez ce cas en conséquence (par exemple, affichez un message d'erreur)
    }
}
