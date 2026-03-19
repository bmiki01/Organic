#include "MainWindow.h"
#include "WebRequest.h"
#include "WelcomeWindow.h"
#include "ui_welcomewindow.h"

WelcomeWindow::WelcomeWindow(QSharedPointer<MainWindow> parent) :
    QWidget(parent.data()),
    ui(new Ui::WelcomeWindow),
    mainWindow(parent)
{
    ui->setupUi(this);
    ui->LEusername->setPlaceholderText("Username");
    ui->LEpassword->setPlaceholderText("Password");
    ui->LEpassword->setEchoMode(QLineEdit::Password);

    connect(ui->PBRegister, &QPushButton::clicked, this, &WelcomeWindow::on_PBregisterClicked);
    connect(ui->PBlogin, &QPushButton::clicked, this, &WelcomeWindow::on_PBloginClicked);
}

void WelcomeWindow::on_PBregisterClicked()
{
    mainWindow->switchToRegistrationWindow(this);
}

void WelcomeWindow::on_PBloginClicked()
{
    QJsonObject body;
    body["username"] = ui->LEusername->text();
    body["password"] = ui->LEpassword->text();

    mainWindow->getRequester().sendPostRequest("http://localhost:8081/api/user/login", body);

    QJsonObject reply = mainWindow->getRequester().getCurrentAnswer();
    QVariant statusCode = mainWindow->getRequester().getStatusCode();

    qDebug() << reply;

    if(statusCode.isValid())
    {
        int statusC = statusCode.toInt();

        // Check if the status code is in the 2xx range
        if (statusC >= 200 && statusC < 300) {
            qDebug() << "HTTP response is OK";

            //FONTOS: a visszakapott adatot átparse-olom saját osztályok objektumaivá a későbbi használat miatt (JSON -> C++):
            mainWindow->getUserData()->Parse(reply);

            int res = mainWindow->getUserData()->isAdmin(0);
            if(res == 0)
            {
                mainWindow->switchToAdminViewhWindow(this);
            }else if(res == 1)
            {
                mainWindow->switchToMainViewWindow(this);
            }else // res = -1
            {
                qDebug() << "Not valid organization index!";
                QMessageBox msgBox;
                msgBox.setText("You are not even in any organization, please enter an existing one or create a new one!");
                msgBox.exec();
                mainWindow->switchToFirstLoginWindow(this);
            }
        } else {
            qDebug() << "HTTP response is not OK. Status code:" << statusC;
            if(statusC == 401)
            {
                qDebug() << "HTTP response is UNAUTHORIZED. Status code:" << statusC;
                QMessageBox msgBox;
                msgBox.setText("Unauthorized username, or incorrect password!");
                msgBox.exec();
            }
        }
    }else {
        // Failed to retrieve the status code
        qDebug() << "Failed to retrieve the HTTP status code";

        QMessageBox msgBox;
        msgBox.setText("Invalid Credentials!");
        msgBox.exec();
    }
}
