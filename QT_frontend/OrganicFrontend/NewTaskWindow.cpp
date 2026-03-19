#include "NewTaskWindow.h"
#include "ui_NewTaskWindow.h"

NewTaskWindow::NewTaskWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewTaskWindow)
{
    ui->setupUi(this);

    ui->CBassign->setPlaceholderText(QStringLiteral("Assign"));
    ui->CBassign->setCurrentIndex(-1);
}

NewTaskWindow::~NewTaskWindow()
{
    delete ui;
}
