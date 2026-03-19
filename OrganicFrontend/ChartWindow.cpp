#include "ChartWindow.h"
#include "ui_ChartWindow.h"

ChartWindow::ChartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);
}

ChartWindow::~ChartWindow()
{
    delete ui;
}
