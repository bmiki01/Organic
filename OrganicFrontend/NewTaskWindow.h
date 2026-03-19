#ifndef NEWTASKWINDOW_H
#define NEWTASKWINDOW_H

#include <QWidget>
#include <QSharedPointer>

namespace Ui {
class NewTaskWindow;
}

class MainWindow;

class NewTaskWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewTaskWindow(QSharedPointer<MainWindow> parent = nullptr);
    void setCurrentOrg(unsigned currentOrg);

private slots:
    void on_createTaskClicked();
    void on_returnClicked();

private:
    QSharedPointer<Ui::NewTaskWindow> ui;
    QSharedPointer<MainWindow> mainWindow;
    unsigned currentOrganization;
};

#endif // NEWTASKWINDOW_H
