#ifndef ADMINVIEWWINDOW_H
#define ADMINVIEWWINDOW_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class AdminViewWindow;
}

class MainWindow;

class AdminViewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminViewWindow(QSharedPointer<MainWindow> parent = nullptr);
    void showOrganizationDetails(unsigned orgIndex = 0);
    void showMemberDetails(unsigned orgIndex, unsigned memberIndex);

private slots:
    void on_newTaskClicked();
    void on_logoutClicked();
    void on_joinORcreateClicked();

private:
    QSharedPointer<Ui::AdminViewWindow> ui;
    QSharedPointer<MainWindow> mainWindow;

    void popupWindow(const QString& str);

    QJsonObject sendRequestOrganization(unsigned int index = 0);
    void handleReply(const QJsonObject& reply);

    QJsonObject sendTasksRequest(QString taskname);
    void handleTasksReply(const QJsonObject& reply);

    void handleOrgNameReply(const QJsonObject& reply);
};

#endif // ADMINVIEWWINDOW_H
