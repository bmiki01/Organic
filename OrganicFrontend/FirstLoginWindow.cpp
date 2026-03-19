#include "FirstLoginWindow.h"
#include "MainWindow.h"
#include "ui_firstloginwindow.h"

FirstLoginWindow::FirstLoginWindow(QSharedPointer<MainWindow> parent) :
    QWidget(parent.data()),
    ui(new Ui::FirstLoginWindow),
    mainWindow(parent)
{
    ui->setupUi(this);

    connect(ui->PBcreateOrganization, &QPushButton::clicked, this, &FirstLoginWindow::on_createOrgClicked);
    connect(ui->PBjoinOrganization, &QPushButton::clicked, this, &FirstLoginWindow::on_joinOrgClicked);
    connect(ui->PBlogout, &QPushButton::clicked, this, &FirstLoginWindow::on_logoutClicked);
}

void FirstLoginWindow::popupWindow(const QString& str)
{
    QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.exec();
}

void FirstLoginWindow::setUserName(const QString& username)
{
    ui->Lwelcome->setText("Welcome, " + username);
}

void FirstLoginWindow::on_createOrgClicked()
{
    bool ok;
    QString organizationName = QInputDialog::getText(nullptr, "Please give a name for your new organization!", "Name: ", QLineEdit::Normal, "", &ok);
    if (ok && !organizationName.isEmpty()) {
        QJsonObject body;
        body["name"] = organizationName;
        body["manager"] = mainWindow->getUserData()->getUsername();

        mainWindow->getRequester().sendPostRequest("http://localhost:8081/api/organization", body);

        QJsonObject reply = mainWindow->getRequester().getCurrentAnswer();
        QVariant statusCode = mainWindow->getRequester().getStatusCode();

        if(statusCode.isValid())
        {
            int statusC = statusCode.toInt();

            if (statusC >= 200 && statusC < 300) {
                qDebug() << "HTTP response is OK. Status code:" << statusC;
                if(statusC == 201)
                {
                    qDebug() << "HTTP response is Created. Status code:" << statusC;
                    mainWindow->getUserData()->addOrganization(organizationName, mainWindow->getUserData()->getUsername());
                    popupWindow("You are created successfully a new organization with the name of: " + organizationName);
                    mainWindow->switchToAdminViewhWindow(this);
                }
            } else {
                qDebug() << "HTTP response is not OK. Status code:" << statusC;
                if(statusC == 409)
                {
                    qDebug() << "HTTP response is Conflict. Status code:" << statusC;
                    QMessageBox msgBox;
                    msgBox.setText("E-mail address is already registered!");
                    msgBox.exec();
                }
            }
        }else {
            qDebug() << "Failed to retrieve the HTTP status code";

                QMessageBox msgBox;
                msgBox.setText("Invalid Credentials!");
                msgBox.exec();
        }
    }else
    {
        popupWindow("Please fill the name textbox!");
    }
}

void FirstLoginWindow::on_joinOrgClicked()
{
    QString url("http://localhost:8081/api/organization/join/" + mainWindow->getUserData()->getUUID());
    qDebug() << mainWindow->getUserData()->getUUID();

    QJsonObject body;
    body["id"] = ui->LEorganizationCode->text();
    qDebug() << ui->LEorganizationCode->text();

    mainWindow->getRequester().sendPostRequest(url, body);

    QJsonObject reply = mainWindow->getRequester().getCurrentAnswer();
    QVariant statusCode = mainWindow->getRequester().getStatusCode();

    if(statusCode.isValid())
    {
        int statusC = statusCode.toInt();

        if (statusC >= 200 && statusC < 300) {
            qDebug() << "HTTP response is OK. Status code:" << statusC;
            if(statusC == 200)
            {
                qDebug() << "HTTP response is Created. Status code:" << statusC;

                mainWindow->getUserData()->addExistingOrganization(reply);

                QJsonValue managerValue = reply.value("manager");
                if(managerValue.toString() == mainWindow->getUserData()->getUsername())
                {
                    mainWindow->switchToAdminViewhWindow(this);
                }else
                {
                    mainWindow->switchToMainViewWindow(this);
                }
            }
        } else {
            qDebug() << "HTTP response is not OK. Status code:" << statusC;
            if(statusC == 409)
            {
                qDebug() << "HTTP response is Conflict. Status code:" << statusC;
                QMessageBox msgBox;
                msgBox.setText("E-mail address is already registered!");
                msgBox.exec();
            }
        }
    }else {
        qDebug() << "Failed to retrieve the HTTP status code";

            QMessageBox msgBox;
            msgBox.setText("Invalid Credentials!");
            msgBox.exec();
    }
}

void FirstLoginWindow::on_logoutClicked()
{
    if(mainWindow->clearSessionUserData())
    {
        mainWindow->switchToWelcomeWindow(this);
    }else
    {
        QMessageBox msgBox;
        msgBox.setText("Failed to clear user session data.");
        msgBox.exec();
    }
}
