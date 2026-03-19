#include "MainWindow.h"
#include "NewTaskWindow.h"
#include "ui_NewTaskWindow.h"

NewTaskWindow::NewTaskWindow(QSharedPointer<MainWindow> parent) :
    QWidget(parent.data()),
    ui(new Ui::NewTaskWindow),
    mainWindow(parent)
{
    ui->setupUi(this);

    ui->LEtaskName->setPlaceholderText(QStringLiteral("Task Name"));

    ui->CBassign->setPlaceholderText(QStringLiteral("Assign"));
    ui->CBassign->setCurrentIndex(-1);

    connect(ui->PBcreateTask, &QPushButton::clicked, this, &NewTaskWindow::on_createTaskClicked);
    connect(ui->PBreturn, &QPushButton::clicked, this, &NewTaskWindow::on_returnClicked);
}


void NewTaskWindow::setCurrentOrg(unsigned currentOrg)
{
    currentOrganization = currentOrg;

    ui->CBassign->clear();
    for(int i = 0; i < mainWindow->getUserData()->getNumberOfMembers(currentOrg); i++)
    {
        ui->CBassign->addItem(mainWindow->getUserData()->getMemberName(currentOrganization, i));
    }
}

void NewTaskWindow::on_returnClicked()
{
    ui->CBassign->clear();
    mainWindow->switchToAdminViewhWindow(this);
}
void NewTaskWindow::on_createTaskClicked()
{
    if(!mainWindow->getUserData()->haveTaskName(ui->LEtaskName->text()))
    {
        if(!ui->LtaskDescription->text().isEmpty())
        {

            QMessageBox msgBox;
            msgBox.setText("Task (" + ui->LEtaskName->text() + ") successfully created for" + ui->CBassign->currentText());
            msgBox.exec();
            Task task;
            task.setName(ui->LEtaskName->text());
            task.setDescription(ui->LtaskDescription->text());
            task.setStatus("ready to start");

            QJsonObject body;
            body["name"] = ui->LEtaskName->text();
            body["description"] = ui->LtaskDescription->text();
            body["organization"] = mainWindow->getUserData()->getFirstOrgName(currentOrganization);
            body["status"] = "READY_TO_START";

            mainWindow->getRequester().sendPostRequest("http://localhost:8081/api/task/" + mainWindow->getUserData()->getUUID(), body);

            QJsonObject reply = mainWindow->getRequester().getCurrentAnswer();
            mainWindow->getUserData()->addTaskToOrganization(currentOrganization, reply["id"].toString(), reply["name"].toString(), reply["status"].toString(), reply["description"].toString());

            mainWindow->switchToAdminViewhWindow(this);
        }else
        {
            QMessageBox msgBox;
            msgBox.setText("Please write description!");
            msgBox.exec();
        }
    }else
    {
        QMessageBox msgBox;
        msgBox.setText("Taskname is already used!");
        msgBox.exec();
    }
}
