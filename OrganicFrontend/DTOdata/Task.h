#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QtCore>

class Task{
private:
    QString uuid;
    QString name;
    QString status;
    QString organization;
    QString description;

public:
    void Parse(const QJsonObject& jsonObject) {
        uuid = jsonObject["id"].toString();
        name = jsonObject["name"].toString();
        status = jsonObject["status"].toString();
        organization = jsonObject["organization"].toString();
        description = jsonObject["description"].toString();
    }
    QString& getId()
    {
        return uuid;
    }

    QString& getName(){
        return name;
    }
    QString& getStatus(){
        return status;
    }
    QString& getDescription(){
        return description;
    }
    void setID(const QString& id){
        this->uuid = id;
    }
    void setName(const QString& n){
        name = n;
    }
    void setStatus(const QString& s){
        status = s;
    }
    void setOrganization(const QString& o){
        organization = o;
    }
    void setDescription(const QString& d){
        description = d;
    }
};

#endif // TASK_H
