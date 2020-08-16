/********************************************************************************
** Form generated from reading UI file 'imgProcessing.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMGPROCESSING_H
#define UI_IMGPROCESSING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imgProcessingClass
{
public:
    QAction *actionnew;
    QAction *actionopen;
    QAction *actionsave;
    QAction *actionclose;
    QAction *actionsaveas;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *imgProcessingClass)
    {
        if (imgProcessingClass->objectName().isEmpty())
            imgProcessingClass->setObjectName(QString::fromUtf8("imgProcessingClass"));
        imgProcessingClass->resize(595, 404);
        actionnew = new QAction(imgProcessingClass);
        actionnew->setObjectName(QString::fromUtf8("actionnew"));
        actionopen = new QAction(imgProcessingClass);
        actionopen->setObjectName(QString::fromUtf8("actionopen"));
        actionsave = new QAction(imgProcessingClass);
        actionsave->setObjectName(QString::fromUtf8("actionsave"));
        actionclose = new QAction(imgProcessingClass);
        actionclose->setObjectName(QString::fromUtf8("actionclose"));
        actionsaveas = new QAction(imgProcessingClass);
        actionsaveas->setObjectName(QString::fromUtf8("actionsaveas"));
        centralWidget = new QWidget(imgProcessingClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        imgProcessingClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(imgProcessingClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 595, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        imgProcessingClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(imgProcessingClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        imgProcessingClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(imgProcessingClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        imgProcessingClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionnew);
        menu->addAction(actionopen);
        menu->addAction(actionsave);
        menu->addAction(actionsaveas);
        menu->addAction(actionclose);
        mainToolBar->addAction(actionnew);
        mainToolBar->addAction(actionopen);

        retranslateUi(imgProcessingClass);

        QMetaObject::connectSlotsByName(imgProcessingClass);
    } // setupUi

    void retranslateUi(QMainWindow *imgProcessingClass)
    {
        imgProcessingClass->setWindowTitle(QCoreApplication::translate("imgProcessingClass", "imgProcessing", nullptr));
        actionnew->setText(QCoreApplication::translate("imgProcessingClass", "\346\226\260\345\273\272", nullptr));
        actionopen->setText(QCoreApplication::translate("imgProcessingClass", "\346\211\223\345\274\200", nullptr));
        actionsave->setText(QCoreApplication::translate("imgProcessingClass", "\344\277\235\345\255\230", nullptr));
        actionclose->setText(QCoreApplication::translate("imgProcessingClass", "\345\205\263\351\227\255", nullptr));
        actionsaveas->setText(QCoreApplication::translate("imgProcessingClass", "\345\217\246\345\255\230\344\270\272", nullptr));
        menu->setTitle(QCoreApplication::translate("imgProcessingClass", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class imgProcessingClass: public Ui_imgProcessingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMGPROCESSING_H
