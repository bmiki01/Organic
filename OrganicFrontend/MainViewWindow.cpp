#include "MainWindow.h"
#include "MainViewWindow.h"
#include "ui_MainViewWindow.h"

MainViewWindow::MainViewWindow(QSharedPointer<MainWindow> parent) :
    QWidget(parent.data()),
    ui(new Ui::MainViewWindow),
    mainWindow(parent)
{
    ui->setupUi(this);

    connect(ui->PBlogout, SIGNAL(&QPushButton::clicked), this, SLOT(&MainViewWindow::on_logoutClicked));
    connect(ui->PBjoin, SIGNAL(&QPushButton::clicked), this, SLOT(&MainViewWindow::on_joinClicked));

    connect(ui->CBselectOrganization, QOverload<int>::of(&QComboBox::activated),[=](int index){
        showOrganizationDetails(index);
    });

    connect(ui->TWtasks, QOverload<QTableWidgetItem*>::of(&QTableWidget::itemClicked),[=](QTableWidgetItem* item){
        if(item->text().isEmpty()) return;
        int taskIndex = item->row();
        qDebug() << taskIndex;
        showTaskDetails(taskIndex);
    });
}

void MainViewWindow::popupWindow(const QString& str)
{
    QMessageBox msgBox;
    msgBox.setText(str);
    msgBox.exec();
}

void MainViewWindow::showOrganizationDetails(unsigned orgIndex)
{
    if(mainWindow->getUserData()->isAdmin(orgIndex) == 0)
    {
        mainWindow->switchToAdminViewhWindow(this, orgIndex);
    }

    ui->LEusername->setText(mainWindow->getUserData()->getUsername());
    ui->label->setText(mainWindow->getUserData()->getFirstOrgName(orgIndex));

    ui->CBselectOrganization->clear();
    for(int i = 0; i < mainWindow->getUserData()->getNumberOfOrganizations(); i++)
    {
        ui->CBselectOrganization->addItem(mainWindow->getUserData()->getFirstOrgName(i));
    }

    ui->TWtasks->clear();
    for (int row = ui->TWtasks->rowCount() - 1; row >= 0; --row) {
        bool isEmpty = true;
        for (int column = 0; column < ui->TWtasks->columnCount(); ++column) {
            QTableWidgetItem* item = ui->TWtasks->item(row, column);
            if (item && !item->text().isEmpty()) {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            ui->TWtasks->removeRow(row);
        }
    }

    int row = 0;
    for (int i = 0; i < mainWindow->getUserData()->getNumberOfTasks(); i++) {
        ui->TWtasks->insertRow(row);

        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(mainWindow->getUserData()->getTaskName(i));
        ui->TWtasks->setItem(row, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(mainWindow->getUserData()->getTaskStatus(i));
        ui->TWtasks->setItem(row, 1, item2);
        row++;
    }
}

void MainViewWindow::showTaskDetails(unsigned taskIndex)
{
    ui->LEtaskName->setText(mainWindow->getUserData()->getTaskName(taskIndex));
    ui->TEdescription->setText(mainWindow->getUserData()->getTaskDescription(taskIndex));
}

void MainViewWindow::on_logoutClicked()
{
    QMessageBox::StandardButton answer;
    answer = QMessageBox::question(nullptr, "Confirmation", "Do you want to logout?", QMessageBox::Yes | QMessageBox::Cancel);

    if (answer == QMessageBox::Cancel)
    {
        return;
    }else if(answer == QMessageBox::Yes)
    {
        if(mainWindow->clearSessionUserData())
        {
            ui->CBselectOrganization->clear();
            ui->TWtasks->clear();
            mainWindow->switchToWelcomeWindow(this);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Failed to clear user session data.");
            msgBox.exec();
        }
    }
}

void MainViewWindow::on_joinClicked()
{
    mainWindow->switchToFirstLoginWindow(this);
}
