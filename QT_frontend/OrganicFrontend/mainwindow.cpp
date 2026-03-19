#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "ui_registration.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    welcomeWindow = new WelcomeWindow(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

