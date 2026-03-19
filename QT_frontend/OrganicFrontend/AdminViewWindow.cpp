#include "AdminViewWindow.h"
#include "ui_AdminViewWindow.h"

AdminViewWindow::AdminViewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminViewWindow)
{
    ui->setupUi(this);

    ui->CBselectOrganization->setPlaceholderText(QStringLiteral("Select Organization"));
    ui->CBselectOrganization->setCurrentIndex(-1);
}

AdminViewWindow::~AdminViewWindow()
{
    delete ui;
}
