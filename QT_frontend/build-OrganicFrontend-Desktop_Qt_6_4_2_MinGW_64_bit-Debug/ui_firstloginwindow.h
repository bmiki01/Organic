/********************************************************************************
** Form generated from reading UI file 'firstloginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTLOGINWINDOW_H
#define UI_FIRSTLOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FirstLoginWindow
{
public:
    QTextEdit *textEdit;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *TEcreateOrganization;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *TEorganizationCode;
    QTextEdit *TEjoinOrganization;
    QPushButton *PBlogout;
    QLabel *labelWelcome;

    void setupUi(QWidget *FirstLoginWindow)
    {
        if (FirstLoginWindow->objectName().isEmpty())
            FirstLoginWindow->setObjectName("FirstLoginWindow");
        FirstLoginWindow->resize(1920, 1080);
        textEdit = new QTextEdit(FirstLoginWindow);
        textEdit->setObjectName("textEdit");
        textEdit->setEnabled(false);
        textEdit->setGeometry(QRect(510, 130, 451, 41));
        verticalLayoutWidget = new QWidget(FirstLoginWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(510, 180, 451, 232));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TEcreateOrganization = new QTextEdit(verticalLayoutWidget);
        TEcreateOrganization->setObjectName("TEcreateOrganization");

        verticalLayout->addWidget(TEcreateOrganization);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        TEorganizationCode = new QTextEdit(verticalLayoutWidget);
        TEorganizationCode->setObjectName("TEorganizationCode");

        horizontalLayout_2->addWidget(TEorganizationCode);

        TEjoinOrganization = new QTextEdit(verticalLayoutWidget);
        TEjoinOrganization->setObjectName("TEjoinOrganization");

        horizontalLayout_2->addWidget(TEjoinOrganization);


        verticalLayout->addLayout(horizontalLayout_2);

        PBlogout = new QPushButton(FirstLoginWindow);
        PBlogout->setObjectName("PBlogout");
        PBlogout->setGeometry(QRect(390, 80, 80, 24));
        labelWelcome = new QLabel(FirstLoginWindow);
        labelWelcome->setObjectName("labelWelcome");
        labelWelcome->setGeometry(QRect(980, 90, 49, 16));

        retranslateUi(FirstLoginWindow);

        QMetaObject::connectSlotsByName(FirstLoginWindow);
    } // setupUi

    void retranslateUi(QWidget *FirstLoginWindow)
    {
        FirstLoginWindow->setWindowTitle(QCoreApplication::translate("FirstLoginWindow", "Form", nullptr));
        textEdit->setHtml(QCoreApplication::translate("FirstLoginWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt;\">To Start, please join or create an organization</span></p></body></html>", nullptr));
        TEcreateOrganization->setHtml(QCoreApplication::translate("FirstLoginWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Create organization</p></body></html>", nullptr));
        TEorganizationCode->setHtml(QCoreApplication::translate("FirstLoginWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Organization code</p></body></html>", nullptr));
        TEjoinOrganization->setHtml(QCoreApplication::translate("FirstLoginWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Join organization</p></body></html>", nullptr));
        PBlogout->setText(QCoreApplication::translate("FirstLoginWindow", "Logout", nullptr));
        labelWelcome->setText(QCoreApplication::translate("FirstLoginWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FirstLoginWindow: public Ui_FirstLoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTLOGINWINDOW_H
