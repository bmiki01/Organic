#include "AdminViewWindow.h"
#include "MainWindow.h"
#include "ui_AdminViewWindow.h"

AdminViewWindow::AdminViewWindow(QSharedPointer<MainWindow> parent) :
    QWidget(parent.data()),
    ui(new Ui::AdminViewWindow),
    mainWindow(parent)
{
    ui->setupUi(this);

    ui->CBselectOrganization->setPlaceholderText(QStringLiteral("Select Organization"));
    ui->CBselectOrganization->setCurrentIndex(0);
    ui->TWmembers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TWtasks->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->PBlogout, &QPushButton::clicked, this, &AdminViewWindow::on_logoutClicked);
    connect(ui->PBnewTask, &QPushButton::clicked, this, &AdminViewWindow::on_newTaskClicked);
    connect(ui->PBjoinORcreate, &QPushButton::clicked, this, &AdminViewWindow::on_joinORcreateClicked);
    //connect(ui->PBshowChart, &QPushButton::clicked, this, &AdminViewWindow::on_showChartClicked);

    connect(ui->CBselectOrganization, QOverload<int>::of(&QComboBox::activated),[=](int index){
        showOrganizationDetails(index);
    });
    connect(ui->TWmembers, QOverload<QTableWidgetItem*>::of(&QTableWidget::itemClicked),[=](QTableWidgetItem* item){
        if(item->text().isEmpty())
            return;
        item->foreground().setColor(Qt::GlobalColor::green);
        item->background().setColor(Qt::GlobalColor::white);
        int orgIndex = ui->CBselectOrganization->currentIndex() + 1;
        int memberIndex = item->row();
        //showMemberDetails(orgIndex, memberIndex);
    });
}

void AdminViewWindow::showOrganizationDetails(unsigned orgIndex)
{
    if(mainWindow->getUserData()->isAdmin(orgIndex) == 1 || mainWindow->getUserData()->isAdmin(orgIndex) == -1)
    {
        mainWindow->switchToMainViewWindow(this, orgIndex);
    }
    ui->LEusername->setText(mainWindow->getUserData()->getUsername());
    ui->label->setText(mainWindow->getUserData()->getFirstOrgName(orgIndex));
    ui->LEcode->setText(mainWindow->getUserData()->getOrgCode(orgIndex));

    ui->CBselectOrganization->clear();
    for(int i = 0; i < mainWindow->getUserData()->getNumberOfOrganizations(); i++)
    {
        ui->CBselectOrganization->addItem(mainWindow->getUserData()->getFirstOrgName(i));
    }

    mainWindow->getRequester().sendGetRequest("http://localhost:8081/api/organization/taskcount/" + ui->LEcode->text());

    QJsonObject reply = mainWindow->getRequester().getCurrentAnswer();
    QJsonArray jsonArray = reply["array"].toArray();

    ui->TWmembers->clear();
    for (int row = ui->TWmembers->rowCount() - 1; row >= 0; --row) {
        bool isEmpty = true;
        for (int column = 0; column < ui->TWmembers->columnCount(); ++column) {
            QTableWidgetItem* item = ui->TWmembers->item(row, column);
            if (item && !item->text().isEmpty()) {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            ui->TWmembers->removeRow(row);
        }
    }

    int row = 0;
    for (int i = 0; i < mainWindow->getUserData()->getNumberOfMembers(orgIndex); i++) {
        ui->TWmembers->insertRow(row);

        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(mainWindow->getUserData()->getMemberName(orgIndex,row));
        ui->TWmembers->setItem(row, 0, item1);

        /*QJsonObject jsonObject = jsonValue.toObject();
        int ongoingValue = jsonObject["count"].toInt();

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(QString::number(ongoingValue));
        ui->TWmembers->setItem(row, 1, item2);*/
        row++;
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
    row = 0;
    for(unsigned i = 0; i < mainWindow->getUserData()->getNumberOfTasks(orgIndex); i++)
    {
        ui->TWtasks->insertRow(row);

        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(mainWindow->getUserData()->getTaskName(orgIndex,i));
        ui->TWtasks->setItem(row, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(mainWindow->getUserData()->getAssigneeName(orgIndex, i));
        ui->TWtasks->setItem(row, 1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setText(mainWindow->getUserData()->getTaskStatus(orgIndex, i));
        ui->TWtasks->setItem(row, 2, item3);

        row++;
    }
}

void AdminViewWindow::showMemberDetails(unsigned orgIndex, unsigned memberIndex)
{

    QJsonObject body;
    mainWindow->getRequester().sendPostRequest("http://localhost:8081/tasks/" + ui->LEusername->text() + "/" + mainWindow->getUserData()->getOrgCode(orgIndex), body);
    QJsonObject reply = mainWindow->getRequester().getCurrentAnswer();
    qDebug() << reply;

    //List every tasks of the selected member:
    int row = 0;
    for (int i = 0; i < mainWindow->getUserData()->getNumberOfTasks(orgIndex); ++i) {

        /*ui->TWtasks->insertRow(i);

        QTableWidgetItem *item1 = new QTableWidgetItem();

        QVariant statusCode = mainWindow->getRequester().getStatusCode();
        item1->setText(mainWindow->getUserData()->getTaskName().toString());
        ui->TWtasks->setItem(row, 0, item1);

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(assignees[i].toString());
        ui->TWtasks->setItem(row, 1, item2);

        QTableWidgetItem *item3 = new QTableWidgetItem();
        item2->setText(statuses[i].toString());
        ui->TWtasks->setItem(row, 2, item3);
        row++;*/
    }
}

void AdminViewWindow::on_logoutClicked()
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
            ui->TWmembers->clear();
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

void AdminViewWindow::on_newTaskClicked()
{
    mainWindow->switchToNewTaskWindow(this, ui->CBselectOrganization->currentIndex()+1);
}

void AdminViewWindow::on_joinORcreateClicked()
{
    mainWindow->switchToFirstLoginWindow(this);
}
