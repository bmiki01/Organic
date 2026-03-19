/********************************************************************************
** Form generated from reading UI file 'NewTaskWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWTASKWINDOW_H
#define UI_NEWTASKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewTaskWindow
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *TEtaskName;
    QComboBox *CBassign;
    QLabel *LtaskDescription;
    QTextEdit *TEtext;
    QPushButton *PBcreateTask;

    void setupUi(QWidget *NewTaskWindow)
    {
        if (NewTaskWindow->objectName().isEmpty())
            NewTaskWindow->setObjectName("NewTaskWindow");
        NewTaskWindow->resize(1920, 1008);
        verticalLayoutWidget = new QWidget(NewTaskWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(220, 30, 601, 441));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TEtaskName = new QTextEdit(verticalLayoutWidget);
        TEtaskName->setObjectName("TEtaskName");

        verticalLayout->addWidget(TEtaskName);

        CBassign = new QComboBox(verticalLayoutWidget);
        CBassign->setObjectName("CBassign");

        verticalLayout->addWidget(CBassign);

        LtaskDescription = new QLabel(verticalLayoutWidget);
        LtaskDescription->setObjectName("LtaskDescription");

        verticalLayout->addWidget(LtaskDescription);

        TEtext = new QTextEdit(verticalLayoutWidget);
        TEtext->setObjectName("TEtext");

        verticalLayout->addWidget(TEtext);

        PBcreateTask = new QPushButton(NewTaskWindow);
        PBcreateTask->setObjectName("PBcreateTask");
        PBcreateTask->setGeometry(QRect(740, 500, 80, 24));

        retranslateUi(NewTaskWindow);

        QMetaObject::connectSlotsByName(NewTaskWindow);
    } // setupUi

    void retranslateUi(QWidget *NewTaskWindow)
    {
        NewTaskWindow->setWindowTitle(QCoreApplication::translate("NewTaskWindow", "Form", nullptr));
        LtaskDescription->setText(QCoreApplication::translate("NewTaskWindow", "Task Description", nullptr));
        PBcreateTask->setText(QCoreApplication::translate("NewTaskWindow", "Create Task", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewTaskWindow: public Ui_NewTaskWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWTASKWINDOW_H
