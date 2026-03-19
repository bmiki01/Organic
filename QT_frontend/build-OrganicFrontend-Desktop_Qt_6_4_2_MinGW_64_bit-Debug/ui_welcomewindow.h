/********************************************************************************
** Form generated from reading UI file 'welcomewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOMEWINDOW_H
#define UI_WELCOMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomeWindow
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *PBregister;
    QPushButton *PBlogin;
    QTextEdit *textEdit;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *LEusername;
    QLineEdit *LEpassword;
    QLineEdit *urlLineEdit;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;
    QPushButton *getButton;
    QPushButton *postButton;

    void setupUi(QWidget *WelcomeWindow)
    {
        if (WelcomeWindow->objectName().isEmpty())
            WelcomeWindow->setObjectName("WelcomeWindow");
        WelcomeWindow->resize(1920, 1080);
        horizontalLayoutWidget = new QWidget(WelcomeWindow);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(290, 400, 481, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        PBregister = new QPushButton(horizontalLayoutWidget);
        PBregister->setObjectName("PBregister");

        horizontalLayout->addWidget(PBregister);

        PBlogin = new QPushButton(horizontalLayoutWidget);
        PBlogin->setObjectName("PBlogin");

        horizontalLayout->addWidget(PBlogin);

        textEdit = new QTextEdit(WelcomeWindow);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(410, 130, 201, 41));
        textEdit->setReadOnly(true);
        verticalLayoutWidget = new QWidget(WelcomeWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(390, 210, 241, 161));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        LEusername = new QLineEdit(verticalLayoutWidget);
        LEusername->setObjectName("LEusername");
        LEusername->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(LEusername);

        LEpassword = new QLineEdit(verticalLayoutWidget);
        LEpassword->setObjectName("LEpassword");
        LEpassword->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(LEpassword);

        urlLineEdit = new QLineEdit(WelcomeWindow);
        urlLineEdit->setObjectName("urlLineEdit");
        urlLineEdit->setGeometry(QRect(250, 510, 411, 24));
        label = new QLabel(WelcomeWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(190, 510, 49, 16));
        plainTextEdit = new QPlainTextEdit(WelcomeWindow);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(190, 540, 581, 171));
        getButton = new QPushButton(WelcomeWindow);
        getButton->setObjectName("getButton");
        getButton->setGeometry(QRect(690, 510, 80, 24));
        postButton = new QPushButton(WelcomeWindow);
        postButton->setObjectName("postButton");
        postButton->setGeometry(QRect(780, 510, 80, 24));

        retranslateUi(WelcomeWindow);

        QMetaObject::connectSlotsByName(WelcomeWindow);
    } // setupUi

    void retranslateUi(QWidget *WelcomeWindow)
    {
        WelcomeWindow->setWindowTitle(QCoreApplication::translate("WelcomeWindow", "Form", nullptr));
        PBregister->setText(QCoreApplication::translate("WelcomeWindow", "Register", nullptr));
        PBlogin->setText(QCoreApplication::translate("WelcomeWindow", "Login", nullptr));
        textEdit->setHtml(QCoreApplication::translate("WelcomeWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">Welcome to Organic</span></p></body></html>", nullptr));
        LEusername->setText(QCoreApplication::translate("WelcomeWindow", "username...", nullptr));
        LEpassword->setText(QCoreApplication::translate("WelcomeWindow", "password...", nullptr));
        label->setText(QCoreApplication::translate("WelcomeWindow", "URL tes:", nullptr));
        getButton->setText(QCoreApplication::translate("WelcomeWindow", "GET", nullptr));
        postButton->setText(QCoreApplication::translate("WelcomeWindow", "POST", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WelcomeWindow: public Ui_WelcomeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEWINDOW_H
