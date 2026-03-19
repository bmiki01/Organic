#ifndef MAINVIEWWINDOW_H
#define MAINVIEWWINDOW_H

#include <QWidget>

namespace Ui {
class MainViewWindow;
}

class MainViewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainViewWindow(QWidget *parent = nullptr);
    ~MainViewWindow();

private:
    Ui::MainViewWindow *ui;
};

#endif // MAINVIEWWINDOW_H
