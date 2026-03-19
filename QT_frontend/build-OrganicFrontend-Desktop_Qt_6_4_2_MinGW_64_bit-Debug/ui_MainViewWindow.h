/********************************************************************************
** Form generated from reading UI file 'MainViewWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVIEWWINDOW_H
#define UI_MAINVIEWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainViewWindow
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
    QTextEdit *textEdit_5;
    QListWidget *listWidget;

    void setupUi(QWidget *MainViewWindow)
    {
        if (MainViewWindow->objectName().isEmpty())
            MainViewWindow->setObjectName("MainViewWindow");
        MainViewWindow->resize(1920, 1080);
        verticalLayoutWidget = new QWidget(MainViewWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 491, 591));
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
        textEdit_5 = new QTextEdit(verticalLayoutWidget);
        textEdit_5->setObjectName("textEdit_5");

        verticalLayout_6->addWidget(textEdit_5);

        listWidget = new QListWidget(verticalLayoutWidget);
        listWidget->setObjectName("listWidget");

        verticalLayout_6->addWidget(listWidget);


        HLdown->addLayout(verticalLayout_6);


        verticalLayout->addLayout(HLdown);


        retranslateUi(MainViewWindow);

        QMetaObject::connectSlotsByName(MainViewWindow);
    } // setupUi

    void retranslateUi(QWidget *MainViewWindow)
    {
        MainViewWindow->setWindowTitle(QCoreApplication::translate("MainViewWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainViewWindow: public Ui_MainViewWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEWWINDOW_H
