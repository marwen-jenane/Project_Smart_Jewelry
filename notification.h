#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QSystemTrayIcon>
#include<QString>

class notification
{
public:
    notification();
        void NotificationAjouterFournisseur();
        void NotificationModifierFournisseur();
        void NotificationSupprimerFournisseur();
        void notification_failed();
};

#endif // NOTIFICATION_H
