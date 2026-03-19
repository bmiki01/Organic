#ifndef FIRSTLOGINWINDOW_H
#define FIRSTLOGINWINDOW_H

#include <QMessageBox.h>
#include <QTimer.h>
#include <QWidget>
#include <QInputDialog>
#include <QMessageBox>
#include <QUrl>
#include <QJsonObject>

namespace Ui {
class FirstLoginWindow;
}

class MainWindow;

class FirstLoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FirstLoginWindow(QSharedPointer<MainWindow> parent = nullptr);
    void setUserName(const QString& username);

private slots:
    void on_createOrgClicked();
    void on_joinOrgClicked();
    void on_logoutClicked();

private:
    QSharedPointer<Ui::FirstLoginWindow> ui;
    QSharedPointer<MainWindow> mainWindow;

    void popupWindow(const QString& str);
    QJsonObject sendRequest(const QString& createORjoin, const QString& queryname, const QString& oNorC);
    bool handleReplyCreateOrg(const QJsonObject& reply);
    bool handleReplyJoinOrg(const QJsonObject& reply);
    bool handleNewOrgRequest(const QString& oN);
    bool handleJoinOrgRequest(const QString& oC);
};

#endif // FIRSTLOGINWINDOW_H
