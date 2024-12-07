/********************************************************************************
** Form generated from reading UI file 'Tema89.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMA89_H
#define UI_TEMA89_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tema89Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Tema89Class)
    {
        if (Tema89Class->objectName().isEmpty())
            Tema89Class->setObjectName("Tema89Class");
        Tema89Class->resize(600, 400);
        menuBar = new QMenuBar(Tema89Class);
        menuBar->setObjectName("menuBar");
        Tema89Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Tema89Class);
        mainToolBar->setObjectName("mainToolBar");
        Tema89Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Tema89Class);
        centralWidget->setObjectName("centralWidget");
        Tema89Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Tema89Class);
        statusBar->setObjectName("statusBar");
        Tema89Class->setStatusBar(statusBar);

        retranslateUi(Tema89Class);

        QMetaObject::connectSlotsByName(Tema89Class);
    } // setupUi

    void retranslateUi(QMainWindow *Tema89Class)
    {
        Tema89Class->setWindowTitle(QCoreApplication::translate("Tema89Class", "Tema89", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tema89Class: public Ui_Tema89Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMA89_H
