#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <QDebug>
#include <QCoreApplication>
#include <QVariant>
#include <QUuid>

class WebRequest : public QObject
{
    Q_OBJECT

public:
    explicit WebRequest()
        : QObject(nullptr)
    {
        manager = new QNetworkAccessManager(this);
        currentAnswer = QJsonObject();
        currentStatusCode = QVariant();
        arrivedReply = false;

        //Initialize for UUID:
        uuidObject = QUuid::createUuid();

        connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    }

    const QString& getUUID()
    {
        return uuidObject.toString();
    }

    void setUUID(QString uuidString)
    {
        uuidObject = QUuid::fromString(uuidString);
    }

    virtual ~WebRequest() {
        delete manager;
    }

    void sendGetRequest(const QUrl& url = QUrl("https://www.google.com/"))
    {
        QNetworkRequest request;
        request.setUrl(url);
        request.setRawHeader("User-Agent", "DemoBrowser 1.0");

        std::cout << "->Sending HTTP GET request..." << std::endl;
        QNetworkReply *reply = manager->get(request);
        connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(slotError(QNetworkReply::NetworkError)));
        connect(reply, SIGNAL(sslErrors(QList<QSslError>)),this, SLOT(slotSslErrors(QList<QSslError>)));
    }

    void sendPostRequest(const QString& url, QJsonObject &body)
    {
        QNetworkRequest request;
        request.setUrl(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QByteArray postData = QJsonDocument(body).toJson();
        QNetworkReply *reply = manager->post(request, postData);

        qDebug() << "->Sending HTTP POST Request...";
        connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(slotError(QNetworkReply::NetworkError)));
        connect(reply, SIGNAL(sslErrors(QList<QSslError>)),this, SLOT(slotSslErrors(QList<QSslError>)));
    }

    QJsonObject getCurrentAnswer()
    {
        while(!arrivedReply)
            QCoreApplication::processEvents();
        arrivedReply = false;
        return currentAnswer;
    }

    QVariant getStatusCode()
    {
        return currentStatusCode;
    }

public slots:
    void replyFinished(QNetworkReply* reply)
    {
        qDebug() << "Received a response from this URL:" << reply->url().toEncoded();
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        currentAnswer = doc.object();
        currentStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug() << "STATUS CODE:" << currentStatusCode.toString();
        arrivedReply = true;

        reply->deleteLater();
    }

    void slotReadyRead()
    {
        qDebug() << "- Data received...";
    }

    void slotError(QNetworkReply::NetworkError)
    {
        qDebug() << "- Communication error. :(";
    }

    void slotSslErrors(QList<QSslError>)
    {
        qDebug() << "- SSL error. :(";
    }

private:
    QNetworkAccessManager *manager = nullptr;
    QJsonObject currentAnswer;
    QVariant currentStatusCode;
    bool arrivedReply;
    QUuid uuidObject;
};

#endif // WEBREQUEST_H
