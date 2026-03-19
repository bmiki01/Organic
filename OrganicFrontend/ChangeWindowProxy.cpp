#include "ChangeWindowProxy.h"
#include "MainWindow.h"

ChangeWindowProxy* ChangeWindowProxy::instance = nullptr;

ChangeWindowProxy::ChangeWindowProxy(MainWindow &_mainWindow):mainWindow(_mainWindow){}

void ChangeWindowProxy::switchToAdminViewhWindow(QWidget* from){
    //mainWindow->switchToAdminViewhWindow(from);
}

void ChangeWindowProxy::switchToFirstLoginWindow(QWidget* from){
    //mainWindow->switchToFirstLoginWindow(from);
}

void ChangeWindowProxy::switchToMainViewWindow(QWidget* from){
    //mainWindow->switchToFirstLoginWindow(from);
}

void ChangeWindowProxy::switchToNewTaskWindow(QWidget* from){
    //mainWindow->switchToNewTaskWindow(from);
}

void ChangeWindowProxy::switchToRegistrationWindow(QWidget* from){
    //mainWindow->switchToRegistrationWindow(from);
}

void ChangeWindowProxy::switchToWelcomeWindow(QWidget* from){
    //mainWindow->switchToWelcomeWindow(from);
}
