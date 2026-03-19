#ifndef ADMINVIEWWINDOW_H
#define ADMINVIEWWINDOW_H

#include <QWidget>

namespace Ui {
class AdminViewWindow;
}

class AdminViewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminViewWindow(QWidget *parent = nullptr);
    ~AdminViewWindow();

private:
    Ui::AdminViewWindow *ui;
};

#endif // ADMINVIEWWINDOW_H
