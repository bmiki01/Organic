#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QList>

#include "Task.h"

class Organization{
private:
    QString uuidObject;
    QString name;
    QList<Task> tasks;
    QString manager;
    QList<QString> assignees;
public:

    Organization()
    {

    }

    Organization(const QString& n, const QList<Task>& t, const QString& m, const QList<QString>& a)
        : name(n), tasks(t), manager(m), assignees(a)
    {

    }

    void Parse(const QJsonObject& jsonObject)
    {
        uuidObject = jsonObject["id"].toString();
        name = jsonObject["name"].toString();
        manager = jsonObject["manager"].toString();

        tasks.clear();
        QJsonArray taskArray = jsonObject["tasks"].toArray();
        for (const QJsonValue& taskValue : taskArray) {
            Task task;
            task.Parse(taskValue.toObject());
            tasks.append(task);
        }

        assignees.clear();
        QJsonArray assigneeArray = jsonObject["assignee"].toArray();
        for (const QJsonValue& assigneeValue : assigneeArray) {
            assignees.append(assigneeValue.toString());
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
    QString getManager()
    {
        return this->manager;
    }
    QString getName()
    {
        return this->name;
    }
    const QString& getTaskName(int i)
    {
        return tasks[i].getName();
    }
    const QString& getStatus(int i)
    {
        return tasks[i].getStatus();
    }
    const QString& getDescription(int i)
    {
        return tasks[i].getDescription();
    }
    int getNumberOfTasks()
    {
        return tasks.size();
    }
    int getNumberOfMembers()
    {
        return assignees.size();
    }
    const QString& getName(int i)
    {
        return assignees[i];
    }
    void addTask(QString id, QString name, QString status, QString description)
    {
        Task newTask;
        newTask.setID(id);
        newTask.setName(name);
        newTask.setStatus(status);
        newTask.setDescription(description);
        tasks.append(newTask);
    }
};


#endif // ORGANIZATION_H
