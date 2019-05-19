/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *createAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *knotAction;
    QAction *curveAction;
    QAction *helpAction;
    QAction *onProgramAction;
    QAction *cancelAction;
    QAction *repeatAction;
    QAction *deleteAction;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *correctionMenu;
    QMenu *viewMenu;
    QMenu *addMenu;
    QMenu *helpMenu;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        createAction = new QAction(MainWindow);
        createAction->setObjectName(QString::fromUtf8("createAction"));
        openAction = new QAction(MainWindow);
        openAction->setObjectName(QString::fromUtf8("openAction"));
        saveAction = new QAction(MainWindow);
        saveAction->setObjectName(QString::fromUtf8("saveAction"));
        saveAsAction = new QAction(MainWindow);
        saveAsAction->setObjectName(QString::fromUtf8("saveAsAction"));
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        knotAction = new QAction(MainWindow);
        knotAction->setObjectName(QString::fromUtf8("knotAction"));
        knotAction->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/Resources/cloud.png"), QSize(), QIcon::Normal, QIcon::Off);
        knotAction->setIcon(icon);
        curveAction = new QAction(MainWindow);
        curveAction->setObjectName(QString::fromUtf8("curveAction"));
        helpAction = new QAction(MainWindow);
        helpAction->setObjectName(QString::fromUtf8("helpAction"));
        onProgramAction = new QAction(MainWindow);
        onProgramAction->setObjectName(QString::fromUtf8("onProgramAction"));
        cancelAction = new QAction(MainWindow);
        cancelAction->setObjectName(QString::fromUtf8("cancelAction"));
        repeatAction = new QAction(MainWindow);
        repeatAction->setObjectName(QString::fromUtf8("repeatAction"));
        deleteAction = new QAction(MainWindow);
        deleteAction->setObjectName(QString::fromUtf8("deleteAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
        correctionMenu = new QMenu(menubar);
        correctionMenu->setObjectName(QString::fromUtf8("correctionMenu"));
        viewMenu = new QMenu(menubar);
        viewMenu->setObjectName(QString::fromUtf8("viewMenu"));
        addMenu = new QMenu(menubar);
        addMenu->setObjectName(QString::fromUtf8("addMenu"));
        helpMenu = new QMenu(menubar);
        helpMenu->setObjectName(QString::fromUtf8("helpMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(correctionMenu->menuAction());
        menubar->addAction(viewMenu->menuAction());
        menubar->addAction(addMenu->menuAction());
        menubar->addAction(helpMenu->menuAction());
        fileMenu->addAction(createAction);
        fileMenu->addAction(openAction);
        fileMenu->addSeparator();
        fileMenu->addAction(saveAction);
        fileMenu->addAction(saveAsAction);
        fileMenu->addSeparator();
        fileMenu->addAction(exitAction);
        correctionMenu->addAction(cancelAction);
        correctionMenu->addAction(repeatAction);
        correctionMenu->addSeparator();
        correctionMenu->addAction(deleteAction);
        addMenu->addAction(knotAction);
        addMenu->addAction(curveAction);
        helpMenu->addAction(helpAction);
        helpMenu->addAction(onProgramAction);
        toolBar->addAction(knotAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        createAction->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        openAction->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        saveAction->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        saveAsAction->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272...", nullptr));
        exitAction->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        knotAction->setText(QApplication::translate("MainWindow", "\320\243\320\267\320\265\320\273", nullptr));
        curveAction->setText(QApplication::translate("MainWindow", "\320\241\320\262\321\217\320\267\321\214", nullptr));
        helpAction->setText(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        onProgramAction->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        cancelAction->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        repeatAction->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214", nullptr));
        deleteAction->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        fileMenu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        correctionMenu->setTitle(QApplication::translate("MainWindow", "\320\237\321\200\320\260\320\262\320\272\320\260", nullptr));
        viewMenu->setTitle(QApplication::translate("MainWindow", "\320\222\320\270\320\264", nullptr));
        addMenu->setTitle(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        helpMenu->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
