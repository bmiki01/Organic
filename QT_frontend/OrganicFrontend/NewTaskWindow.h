#ifndef NEWTASKWINDOW_H
#define NEWTASKWINDOW_H

#include <QWidget>

namespace Ui {
class NewTaskWindow;
}

class NewTaskWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewTaskWindow(QWidget *parent = nullptr);
    ~NewTaskWindow();

private:
    Ui::NewTaskWindow *ui;
};

#endif // NEWTASKWINDOW_H
