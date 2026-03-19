#include "firstloginwindow.h"
#include "ui_firstloginwindow.h"

FirstLoginWindow::FirstLoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstLoginWindow)
{
    ui->setupUi(this);
}

FirstLoginWindow::~FirstLoginWindow()
{
    delete ui;
}
