#include "MainWindow.h"
#include "RegistrationWindow.h"
#include "ui_RegistrationWindow.h"

RegistrationWindow::RegistrationWindow(QSharedPointer<MainWindow> parent) :
    QWidget(parent.data()),
    ui(new Ui::RegistrationWindow),
    mainWindow(parent)
{
    ui->setupUi(this);
    ui->LEemail->setPlaceholderText("E-mail");
    ui->LEusername->setPlaceholderText("Username");
    ui->LEpassword->setPlaceholderText("Password");
    ui->LEpassword->setEchoMode(QLineEdit::Password);
    ui->LEconfirmPW->setPlaceholderText("Confirm Password");
    ui->LEconfirmPW->setEchoMode(QLineEdit::Password);

    connect(ui->PBlogout, SIGNAL(&QPushButton::clicked), this, SLOT(&RegistrationWindow::on_logoutClicked));
    connect(ui->CLBregister, &QCommandLinkButton::clicked, this, &RegistrationWindow::on_CLBregisterClicked);
}

void RegistrationWindow::popupWindow(const QString& str)
{
    QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.exec();
}

bool RegistrationWindow::isAllInformationFilled() const
{
    return(ui->LEemail->text() != "" &&
           ui->LEusername->text() != "" &&
           ui->LEpassword->text() != "" &&
           ui->LEconfirmPW->text() != "");
}

bool RegistrationWindow::arePasswordsMatching() const
{
    return(ui->LEpassword->text() == ui->LEconfirmPW->text());
}

void RegistrationWindow::on_CLBregisterClicked()
{
    if(isAllInformationFilled())
    {
        if(!arePasswordsMatching())
        {
            popupWindow("Passwords do not match!");
            return;
        }

        QJsonObject body;
        body["email"] = ui->LEemail->text();
        body["username"] = ui->LEusername->text();
        body["password"] = ui->LEpassword->text();

        mainWindow->getRequester().sendPostRequest("http://localhost:8081/api/user", body);

        QJsonObject reply = mainWindow->getRequester().getCurrentAnswer();
        qDebug() << reply;
        QVariant statusCode = mainWindow->getRequester().getStatusCode();

        if(statusCode.isValid())
        {
            int statusC = statusCode.toInt();

            if (statusC >= 200 && statusC < 300) {
                qDebug() << "HTTP response is OK. Status code:" << statusC;
                if(statusC == 201)
                {
                    qDebug() << "HTTP response is Created. Status code:" << statusC;
                    mainWindow->getUserData()->Parse(reply);
                    mainWindow->switchToFirstLoginWindow(this);
                }
            } else {
                qDebug() << "HTTP response is not OK. Status code:" << statusC;
                if(statusC == 409)
                {
                    qDebug() << "HTTP response is Conflict. Status code:" << statusC;
                    QMessageBox msgBox;
                    msgBox.setText("The given E-mail address or username is already used!");
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
        popupWindow("Please fill out all information!");
    }
}

void RegistrationWindow::on_logoutClicked()
{
    if(mainWindow->clearSessionUserData())
    {
        mainWindow->switchToWelcomeWindow(this);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Failed to clear user session data.");
        msgBox.exec();
    }
}
