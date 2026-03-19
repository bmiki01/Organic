#include <iostream>
#include <QNetworkAccessManager.h>
#include <QNetworkReply.h>
#include <QNetworkRequest.h>

#include "welcomewindow.h"
#include "ui_welcomewindow.h"

WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);

    mManager = new QNetworkAccessManager(this);

    //connect(signalObject, signal, slotObject, slot)
    connect(mManager, &QNetworkAccessManager::finished, this, [&](QNetworkReply* reply)
    {
        QByteArray data = reply->readAll();
        QString str = QString::fromLatin1(data);
        std::cout << str.toStdString() << std::endl;
        ui->plainTextEdit->setPlainText(str);
    });

    connect(ui->LEusername, &QLineEdit::textChanged, this, &WelcomeWindow::on_LEusername_text_changed);
    connect(ui->LEpassword, &QLineEdit::textChanged, this, &WelcomeWindow::on_LEpassword_text_changed);

    connect(ui->PBregister, &QPushButton::clicked, this, &WelcomeWindow::on_PBregister_clicked_slot);
    connect(ui->PBlogin, &QPushButton::clicked, this, &WelcomeWindow::on_PBlogin_clicked_slot);
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::on_getButton_clicked()
{
    mManager->get(QNetworkRequest(QUrl(ui->urlLineEdit->text())));
}


void WelcomeWindow::on_postButton_clicked()
{
    //mManager->post(QNetworkReply(QUrl(ui->urlLineEdit->text())));
}

void WelcomeWindow::on_LEusername_text_changed()
{

}

void WelcomeWindow::on_LEpassword_text_changed()
{

}

void WelcomeWindow::on_PBregister_clicked_slot()
{
    std::cout << "Hello Button!" << std::endl;
    registrationWindow = new RegistrationWindow(this->parentWidget());
    registrationWindow->show();
    this->hide();
}

void WelcomeWindow::on_PBlogin_clicked_slot()
{

}
