#include "MainWindow.h"

#include <QApplication>
#include <QString>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/resources/styleSheet/Combinear.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
