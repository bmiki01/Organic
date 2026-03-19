/********************************************************************************
** Form generated from reading UI file 'AdminViewWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINVIEWWINDOW_H
#define UI_ADMINVIEWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminViewWindow
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *HLup;
    QVBoxLayout *verticalLayout_5;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *textEdit_3;
    QTextEdit *textEdit_4;
    QHBoxLayout *HLdown;
    QVBoxLayout *verticalLayout_7;
    QTextEdit *textEdit_6;
    QListWidget *listWidget_2;
    QVBoxLayout *verticalLayout_6;
    QComboBox *CBselectOrganization;
    QTextEdit *textEdit_5;
    QListWidget *listWidget;

    void setupUi(QWidget *AdminViewWindow)
    {
        if (AdminViewWindow->objectName().isEmpty())
            AdminViewWindow->setObjectName("AdminViewWindow");
        AdminViewWindow->resize(1920, 1080);
        verticalLayoutWidget = new QWidget(AdminViewWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(410, 20, 491, 591));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        HLup = new QHBoxLayout();
        HLup->setObjectName("HLup");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        textEdit = new QTextEdit(verticalLayoutWidget);
        textEdit->setObjectName("textEdit");

        verticalLayout_5->addWidget(textEdit);

        textEdit_2 = new QTextEdit(verticalLayoutWidget);
        textEdit_2->setObjectName("textEdit_2");

        verticalLayout_5->addWidget(textEdit_2);


        HLup->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        textEdit_3 = new QTextEdit(verticalLayoutWidget);
        textEdit_3->setObjectName("textEdit_3");

        verticalLayout_4->addWidget(textEdit_3);

        textEdit_4 = new QTextEdit(verticalLayoutWidget);
        textEdit_4->setObjectName("textEdit_4");

        verticalLayout_4->addWidget(textEdit_4);


        HLup->addLayout(verticalLayout_4);


        verticalLayout->addLayout(HLup);

        HLdown = new QHBoxLayout();
        HLdown->setObjectName("HLdown");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        textEdit_6 = new QTextEdit(verticalLayoutWidget);
        textEdit_6->setObjectName("textEdit_6");

        verticalLayout_7->addWidget(textEdit_6);

        listWidget_2 = new QListWidget(verticalLayoutWidget);
        listWidget_2->setObjectName("listWidget_2");

        verticalLayout_7->addWidget(listWidget_2);


        HLdown->addLayout(verticalLayout_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        CBselectOrganization = new QComboBox(verticalLayoutWidget);
        CBselectOrganization->setObjectName("CBselectOrganization");

        verticalLayout_6->addWidget(CBselectOrganization);

        textEdit_5 = new QTextEdit(verticalLayoutWidget);
        textEdit_5->setObjectName("textEdit_5");

        verticalLayout_6->addWidget(textEdit_5);

        listWidget = new QListWidget(verticalLayoutWidget);
        listWidget->setObjectName("listWidget");

        verticalLayout_6->addWidget(listWidget);


        HLdown->addLayout(verticalLayout_6);


        verticalLayout->addLayout(HLdown);


        retranslateUi(AdminViewWindow);

        QMetaObject::connectSlotsByName(AdminViewWindow);
    } // setupUi

    void retranslateUi(QWidget *AdminViewWindow)
    {
        AdminViewWindow->setWindowTitle(QCoreApplication::translate("AdminViewWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AdminViewWindow: public Ui_AdminViewWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINVIEWWINDOW_H
