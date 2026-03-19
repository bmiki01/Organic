#ifndef FIRSTLOGINWINDOW_H
#define FIRSTLOGINWINDOW_H

#include <QWidget>

namespace Ui {
class FirstLoginWindow;
}

class FirstLoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FirstLoginWindow(QWidget *parent = nullptr);
    ~FirstLoginWindow();

private:
    Ui::FirstLoginWindow *ui;
};

#endif // FIRSTLOGINWINDOW_H
