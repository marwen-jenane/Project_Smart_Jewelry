#include "notification.h"
#include <QSystemTrayIcon>
#include<QString>

notification::notification()
{

}
void notification::NotificationAjouterFournisseur()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestions des fournisseurs","Nouveau fournisseur est ajoutée ",QSystemTrayIcon::Information,15000);
}

void notification::NotificationModifierFournisseur()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestions des fournisseurs","Nouveau fournisseur est modifiée",QSystemTrayIcon::Information,15000);
}

void notification::NotificationSupprimerFournisseur()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestions des fournisseurs","Nouveau fournisseur est supprimée",QSystemTrayIcon::Information,15000);
}



















/*
void notification::notification_failed()
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon(":/logo.png"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestions des fournisseurs","Action Failed",QSystemTrayIcon::Critical,15000);
}*/
