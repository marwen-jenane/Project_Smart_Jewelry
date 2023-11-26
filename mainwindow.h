#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fournisseurs.h"
#include <QMainWindow>
#include "notification.h"
#include "historique.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QHBoxLayout>
#include <QtCharts/QLegend>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts>
#include <QBarSet>
#include <QBarSeries>
#include <QLayout>
#include <QVector>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts>
#include <QPieSlice>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   void   statFournisseur();

private slots:
     void on_pb_ajouter_clicked();

     void on_pb_supprimer_clicked();

     void on_pb_miseajour_clicked();

     void on_pb_clear_clicked();

     void on_tab_Fournisseur_activated(const QModelIndex &index);

     void on_x_recherche_textChanged(const QString &arg1);

     void on_comboBox_tri_currentIndexChanged(const QString &arg1);

     void on_pb_PDF_clicked();

     void clearFournisseur_StatisticsChart();
     void update_Fournisseur_StatisticsChart();
     void on_tabWidget_tabBarClicked(int index);



private:
    Ui::MainWindow *ui;
    Fournisseurs F;
    notification N;
    historique H;
    QChartView *FournisseurStatisticsChartView;
};
#endif // MAINWINDOW_H
