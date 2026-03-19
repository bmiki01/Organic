#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QString>
#include <QMessageBox>
#include <QSharedPointer>

namespace Ui {
class RegistrationWindow;
}

class MainWindow;

class RegistrationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QSharedPointer<MainWindow> parent = nullptr);

private slots:
    void on_CLBregisterClicked();
    void on_logoutClicked();

private:
    QSharedPointer<Ui::RegistrationWindow> ui;
    QSharedPointer<MainWindow> mainWindow;

    void popupWindow(const QString& str);
    bool isAllInformationFilled() const;
    bool arePasswordsMatching() const;
};

#endif // REGISTRATIONWINDOW_H
