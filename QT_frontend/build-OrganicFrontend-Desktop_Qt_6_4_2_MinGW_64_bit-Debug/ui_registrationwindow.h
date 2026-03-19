/********************************************************************************
** Form generated from reading UI file 'registrationwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONWINDOW_H
#define UI_REGISTRATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registrationwindow
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *TEemail;
    QLineEdit *LEinvalidEmailAddrress;
    QTextEdit *TEusername;
    QLineEdit *LEusernameTaken;
    QTextEdit *TEpassword;
    QTextEdit *TEconfirmPassword;
    QLineEdit *LEpasswordsMatch;
    QCommandLinkButton *CLBregister;
    QTextEdit *TEnewAccount;

    void setupUi(QWidget *registrationwindow)
    {
        if (registrationwindow->objectName().isEmpty())
            registrationwindow->setObjectName("registrationwindow");
        registrationwindow->setEnabled(true);
        registrationwindow->resize(1920, 1080);
        verticalLayoutWidget = new QWidget(registrationwindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(420, 190, 170, 432));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TEemail = new QTextEdit(verticalLayoutWidget);
        TEemail->setObjectName("TEemail");

        verticalLayout->addWidget(TEemail);

        LEinvalidEmailAddrress = new QLineEdit(verticalLayoutWidget);
        LEinvalidEmailAddrress->setObjectName("LEinvalidEmailAddrress");

        verticalLayout->addWidget(LEinvalidEmailAddrress);

        TEusername = new QTextEdit(verticalLayoutWidget);
        TEusername->setObjectName("TEusername");

        verticalLayout->addWidget(TEusername);

        LEusernameTaken = new QLineEdit(verticalLayoutWidget);
        LEusernameTaken->setObjectName("LEusernameTaken");

        verticalLayout->addWidget(LEusernameTaken);

        TEpassword = new QTextEdit(verticalLayoutWidget);
        TEpassword->setObjectName("TEpassword");

        verticalLayout->addWidget(TEpassword);

        TEconfirmPassword = new QTextEdit(verticalLayoutWidget);
        TEconfirmPassword->setObjectName("TEconfirmPassword");

        verticalLayout->addWidget(TEconfirmPassword);

        LEpasswordsMatch = new QLineEdit(verticalLayoutWidget);
        LEpasswordsMatch->setObjectName("LEpasswordsMatch");

        verticalLayout->addWidget(LEpasswordsMatch);

        CLBregister = new QCommandLinkButton(verticalLayoutWidget);
        CLBregister->setObjectName("CLBregister");

        verticalLayout->addWidget(CLBregister);

        TEnewAccount = new QTextEdit(registrationwindow);
        TEnewAccount->setObjectName("TEnewAccount");
        TEnewAccount->setGeometry(QRect(350, 110, 336, 70));

        retranslateUi(registrationwindow);

        QMetaObject::connectSlotsByName(registrationwindow);
    } // setupUi

    void retranslateUi(QWidget *registrationwindow)
    {
        registrationwindow->setWindowTitle(QCoreApplication::translate("registrationwindow", "Form", nullptr));
        TEemail->setHtml(QCoreApplication::translate("registrationwindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">email</p></body></html>", nullptr));
        TEusername->setHtml(QCoreApplication::translate("registrationwindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">username...</p></body></html>", nullptr));
        TEpassword->setHtml(QCoreApplication::translate("registrationwindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">password...</p></body></html>", nullptr));
        TEconfirmPassword->setHtml(QCoreApplication::translate("registrationwindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">confirm password...</p></body></html>", nullptr));
        CLBregister->setText(QCoreApplication::translate("registrationwindow", "Register", nullptr));
        TEnewAccount->setHtml(QCoreApplication::translate("registrationwindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Register  a new account</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registrationwindow: public Ui_registrationwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONWINDOW_H
