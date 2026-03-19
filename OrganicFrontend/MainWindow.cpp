#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    thisPtr = QSharedPointer<MainWindow>(this);

    QPixmap pixmap(":/resources/images/logo.png");
    int w = ui->Llogo->width();
    int h = ui->Llogo->height();
    ui->Llogo->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    webRequest = new WebRequest();
    userData = new UserData();

    adminViewWindow = QSharedPointer<AdminViewWindow>(new AdminViewWindow(thisPtr));
    adminViewWindow->hide();
    firstLoginWindow = QSharedPointer<FirstLoginWindow>(new FirstLoginWindow(thisPtr));
    firstLoginWindow->hide();
    mainViewWindow = QSharedPointer<MainViewWindow>(new MainViewWindow(thisPtr));
    mainViewWindow->hide();
    newTaskWindow = QSharedPointer<NewTaskWindow>(new NewTaskWindow(thisPtr));
    newTaskWindow->hide();
    registrationWindow = QSharedPointer<RegistrationWindow>(new RegistrationWindow(thisPtr));
    registrationWindow->hide();
    welcomeWindow = QSharedPointer<WelcomeWindow>(new WelcomeWindow(thisPtr));
}

WebRequest& MainWindow::getRequester()
{
    return *webRequest;
}

UserData* MainWindow::getUserData()
{
    if(userData != nullptr)
        return userData;
    else
       return (userData = new UserData());
}
bool MainWindow::clearSessionUserData()
{

    delete userData;
    userData = new UserData();
}

void MainWindow::switchToAdminViewhWindow(QWidget *from, int orgIndex)
{
    from->hide();
    adminViewWindow->showOrganizationDetails(orgIndex);
    adminViewWindow->show();
}

void MainWindow::switchToChartWindow(QWidget* from)
{
    from->hide();
    chartWindow->show();
}

void MainWindow::switchToFirstLoginWindow(QWidget *from)
{
    from->hide();
    firstLoginWindow->show();
    firstLoginWindow->setUserName(userData->getUsername());
}
void MainWindow::switchToMainViewWindow(QWidget *from, int orgIndex)
{
    from->hide();
    mainViewWindow->showOrganizationDetails(orgIndex);
    mainViewWindow->show();
}
void MainWindow::switchToNewTaskWindow(QWidget *from, unsigned orgCode)
{
    from->hide();
    newTaskWindow->setCurrentOrg(orgCode);
    newTaskWindow->show();
}
void MainWindow::switchToRegistrationWindow(QWidget *from)
{
    from->hide();
    registrationWindow->show();
}
void MainWindow::switchToWelcomeWindow(QWidget *from)
{
    from->hide();
    welcomeWindow->show();
}

MainWindow::~MainWindow()
{
    delete userData;
    delete webRequest;
}

void MainWindow::on_actionQuit_triggered()
{
    this->clearSessionUserData();
    QApplication::quit();
}

