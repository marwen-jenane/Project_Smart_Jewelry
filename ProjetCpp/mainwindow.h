#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stock.h>

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


    void on_Ajouter_clicked();

    void on_Supp_clicked();

    void on_modifier_clicked();

private:
    Ui::MainWindow *ui;
    stock s;
};
#endif // MAINWINDOW_H
