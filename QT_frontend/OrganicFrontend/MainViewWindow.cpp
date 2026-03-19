#include "MainViewWindow.h"
#include "ui_MainViewWindow.h"

MainViewWindow::MainViewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainViewWindow)
{
    ui->setupUi(this);
}

MainViewWindow::~MainViewWindow()
{
    delete ui;
}
