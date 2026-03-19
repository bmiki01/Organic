#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager.h>
#include <QNetworkReply.h>
#include <QNetworkRequest.h>
#include <QPixmap.h>

#include "AdminViewWindow.h"
#include "ChartWindow.h"
#include "FirstLoginWindow.h"
#include "MainViewWindow.h"
#include "NewTaskWindow.h"
#include "DTOdata/UserData.h"
#include "RegistrationWindow.h"
#include "WelcomeWindow.h"
#include "WebRequest.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    WebRequest &getRequester();
    UserData *getUserData();
    bool clearSessionUserData();

    void switchToAdminViewhWindow(QWidget* from, int orgIndex = 0);
    void switchToChartWindow(QWidget* from);
    void switchToFirstLoginWindow(QWidget* from);
    void switchToMainViewWindow(QWidget* from, int orgIndex = 0);
    void switchToNewTaskWindow(QWidget* from, unsigned orgCode);
    void switchToRegistrationWindow(QWidget* from);
    void switchToWelcomeWindow(QWidget* from);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

private:
    QSharedPointer<MainWindow> thisPtr;

    Ui::MainWindow *ui;

    WebRequest *webRequest;
    UserData *userData;

    QSharedPointer<AdminViewWindow> adminViewWindow;
    QSharedPointer<ChartWindow> chartWindow;
    QSharedPointer<FirstLoginWindow> firstLoginWindow;
    QSharedPointer<MainViewWindow> mainViewWindow;
    QSharedPointer<NewTaskWindow> newTaskWindow;
    QSharedPointer<RegistrationWindow> registrationWindow;
    QSharedPointer<WelcomeWindow> welcomeWindow;
};
#endif // MAINWINDOW_H
