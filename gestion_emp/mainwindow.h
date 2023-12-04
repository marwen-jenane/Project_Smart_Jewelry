#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employee.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_b_ajouter_clicked();

    void on_b_supp_clicked();

    void on_b_supprimer_clicked();

    void on_b_afficher_clicked();

    void on_b_modifier_clicked();

    void on_b_rechercher_clicked();

    void on_b_tri_emp_clicked();

    void on_b_tri_nom_clicked();



    void on_pb_prime_clicked();

    void on_b_reset_prime_clicked();

    void on_b_conge_clicked();

    void on_b_congea_clicked();

    void on_pb_pdf_clicked();

    void on_le_du_userDateChanged(const QDate &date);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Employee emp;
};
#endif // MAINWINDOW_H
