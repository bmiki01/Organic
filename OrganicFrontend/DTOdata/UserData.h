#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include <QList>
#include <QJsonObject>

#include "Organization.h"
#include "Task.h"

class UserData{
private:
    QString uuidObject;
    QString username;
    QString email;
    QList<Task> tasks;
    QList<Organization> organizations;
public:
    void Parse(const QJsonObject& jsonObject) {
        uuidObject = jsonObject["id"].toString();
        username = jsonObject["username"].toString();
        email = jsonObject["email"].toString();

        tasks.clear();
        QJsonArray taskArray = jsonObject["tasks"].toArray();
        for (const QJsonValue& taskValue : taskArray) {
            Task task;
            task.Parse(taskValue.toObject());
            tasks.append(task);
        }

        organizations.clear();
        QJsonArray organizationArray = jsonObject["organizations"].toArray();
        for (const QJsonValue& organizationValue : organizationArray) {
            Organization organization;
            organization.Parse(organizationValue.toObject());
            organizations.append(organization);
        }
    }

    const QString& getUUID()
    {
        return uuidObject;
    }

    void setUUID(QString uuidString)
    {
        uuidObject = uuidString;
    }
    int isAdmin(const int index){
        if(index >= organizations.size())
            return -1;
        if(this->username.compare(this->organizations[index].getManager()) == 0)
            return 0; // Strings are equal -> this user is the admin of the organization
        else
            return 1; // Strings are NOT equal -> 0
    }

    bool haveTaskName(const QString& name)
    {
        for(int i = 0; i < tasks.size(); i++)
            if(tasks[i].getName() == name)
                return true;
        return false;
    }

    const QString& getUsername()
    {
        return username;
    }

    void addExistingOrganization(QJsonObject org)
    {
        Organization organization;
        organization.Parse(org);
        organizations.append(organization);
    }

    QString getFirstOrgName(unsigned index)
    {
        if(!organizations.isEmpty())
            return organizations[index].getName();
        else
            return "No organizations";
    }
    const QString& getOrgCode(unsigned io)
    {
        return organizations[io].getUUID();
    }
    const QString& getAssigneeName(unsigned io, unsigned it)
    {
        return this->organizations[io].getName(it);
    }
    const QString& getTaskName(unsigned io, unsigned it )
    {
        return this->organizations[io].getTaskName(it);
    }
    const QString& getTaskName(unsigned it )
    {
        return this->tasks[it].getName();
    }
    const QString& getTaskStatus(unsigned io, unsigned it )
    {
        return this->organizations[io].getStatus(it);
    }
    const QString& getTaskStatus(unsigned it )
    {
        return this->tasks[it].getStatus();
    }
    const QString& getTaskDescription(unsigned io, unsigned it)
    {
        return this->organizations[io].getDescription(it);
    }
    const QString& getTaskDescription(unsigned it)
    {
        return this->tasks[it].getDescription();
    }
    int getNumberOfTasks(unsigned io)
    {
        return this->organizations[io].getNumberOfTasks();
    }
    const QString& getMemberName(unsigned orgIndex, int i)
    {
        return this->organizations[orgIndex].getName(i);
    }
    int getNumberOfMembers(unsigned io)
    {
        return this->organizations[io].getNumberOfMembers();
    }
    int getNumberOfOrganizations()
    {
        return this->organizations.size();
    }
    unsigned getNumberOfTasks()
    {
        return this->tasks.size();
    }
    void addTask(Task task)
    {
        tasks.append(task);
    }
    void addOrganization(QString name, QString manager)
    {
        QList<Task> t = QList<Task>();
        QList<QString> a = QList<QString>();
        Organization newOrg(name, t, manager, a);
        organizations.append(newOrg);
    }
    void addTaskToOrganization(unsigned io, QString id, QString name, QString status, QString description )
    {
        organizations[io].addTask(id, name, status, description);
    }
};

#endif // USERDATA_H
