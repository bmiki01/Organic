#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QJsonObject>
#include <QWidget>
#include <iostream>
#include <QVector>
#include <QString>
#include <QMessageBox>
#include <QUrl>
#include <QUrlQuery>
#include <QSharedPointer>

#include "DTOdata/UserData.h"

namespace Ui {
class WelcomeWindow;
}

class MainWindow;
class QNetworkAccessManager;

class WelcomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWindow(QSharedPointer<MainWindow> parent = nullptr);

private slots:
    void on_PBregisterClicked();
    void on_PBloginClicked();

private:
    QSharedPointer<Ui::WelcomeWindow> ui;
    QSharedPointer<MainWindow> mainWindow;
};

#endif // WELCOMEWINDOW_H
