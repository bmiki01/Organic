#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QWidget>
#include "registrationwindow.h"

namespace Ui {
class WelcomeWindow;
}

class QNetworkAccessManager;

class WelcomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();

private slots:
    void on_getButton_clicked();

    void on_postButton_clicked();

    //Line edits:
    void on_LEusername_text_changed();
    void on_LEpassword_text_changed();

    //Buttons:
    void on_PBregister_clicked_slot();
    void on_PBlogin_clicked_slot();

private:
    Ui::WelcomeWindow *ui;
    QNetworkAccessManager *mManager;
    RegistrationWindow *registrationWindow;
};

#endif // WELCOMEWINDOW_H
