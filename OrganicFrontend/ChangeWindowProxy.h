#ifndef CHANGEWINDOWPROXY_H
#define CHANGEWINDOWPROXY_H

#include <qwidget.h>

class MainWindow;

class ChangeWindowProxy
{
private:
    MainWindow &mainWindow;

public:
    ChangeWindowProxy(MainWindow &_mainWindow);
    //void switchWindow(QWidget *from, QWidget* to);
    void switchToAdminViewhWindow(QWidget* from);
    void switchToFirstLoginWindow(QWidget* from);
    void switchToMainViewWindow(QWidget* from);
    void switchToNewTaskWindow(QWidget* from);
    void switchToRegistrationWindow(QWidget* from);
    void switchToWelcomeWindow(QWidget* from);
};

#endif // CHANGEWINDOWPROXY_H
