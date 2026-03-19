#ifndef SIGNALQUIT_H
#define SIGNALQUIT_H

#include <QObject>
#include <QCoreApplication>

class SignalQuit : public QObject
{
    Q_OBJECT
public:
    explicit SignalQuit() : QObject(nullptr){}
    virtual ~SignalQuit() {}
public slots:
    void Quit()
    {
        QCoreApplication::quit();
    }
};

#endif // SIGNALQUIT_H
