#ifndef MAINVIEWWINDOW_H
#define MAINVIEWWINDOW_H

#include <QList>
#include <QWidget>
#include <QJsonArray>
#include <QInputDialog>
#include <QMessageBox>
#include <QTableWidgetItem>

namespace Ui {
class MainViewWindow;
}

class MainWindow;

class MainViewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainViewWindow(QSharedPointer<MainWindow> parent = nullptr);
    void showOrganizationDetails(unsigned orgIndex = 0);
    void showTaskDetails(unsigned taskIndex);

private slots:
    void on_logoutClicked();
    void on_joinClicked();

private:
    QSharedPointer<Ui::MainViewWindow> ui;
    QSharedPointer<MainWindow> mainWindow;

    void popupWindow(const QString& str);
    QJsonObject sendRequestOrganization(unsigned int index = 0);
    void handleReply(const QJsonObject& reply);
    QJsonObject sendTaskRequest(QString taskname);
    void handleTaskReply(const QJsonObject& reply);
};

#endif // MAINVIEWWINDOW_H
