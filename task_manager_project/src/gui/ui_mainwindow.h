/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *System_Tab;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QWidget *Processes_Tab;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *treeWidget_2;
    QWidget *Resources_Tab;
    QCustomPlot *CPUGraph;
    QCustomPlot *MemSwapGraph;
    QLabel *label_14;
    QLabel *label_15;
    QCustomPlot *NetworkGraph;
    QLabel *label_16;
    QWidget *FileSystem_Tab;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QMenuBar *menubar;
    QMenu *menuTask;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(735, 765);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMouseTracking(false);
        System_Tab = new QWidget();
        System_Tab->setObjectName(QString::fromUtf8("System_Tab"));
        label = new QLabel(System_Tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 80, 71, 16));
        label_2 = new QLabel(System_Tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 150, 111, 16));
        label_4 = new QLabel(System_Tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(9, 122, 16, 16));
        label_5 = new QLabel(System_Tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 100, 61, 16));
        label_6 = new QLabel(System_Tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 120, 71, 16));
        label_3 = new QLabel(System_Tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 170, 141, 16));
        label_7 = new QLabel(System_Tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(100, 100, 361, 16));
        label_7->setScaledContents(false);
        label_8 = new QLabel(System_Tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(110, 120, 351, 16));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setWordWrap(true);
        label_9 = new QLabel(System_Tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 10, 111, 16));
        label_10 = new QLabel(System_Tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(40, 30, 421, 16));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);
        label_11 = new QLabel(System_Tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(40, 50, 421, 16));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setLineWidth(0);
        label_12 = new QLabel(System_Tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(175, 170, 291, 16));
        tabWidget->addTab(System_Tab, QString());
        Processes_Tab = new QWidget();
        Processes_Tab->setObjectName(QString::fromUtf8("Processes_Tab"));
        verticalLayout_2 = new QVBoxLayout(Processes_Tab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        treeWidget_2 = new QTreeWidget(Processes_Tab);
        treeWidget_2->setObjectName(QString::fromUtf8("treeWidget_2"));

        verticalLayout_2->addWidget(treeWidget_2);

        tabWidget->addTab(Processes_Tab, QString());
        Resources_Tab = new QWidget();
        Resources_Tab->setObjectName(QString::fromUtf8("Resources_Tab"));
        CPUGraph = new QCustomPlot(Resources_Tab);
        CPUGraph->setObjectName(QString::fromUtf8("CPUGraph"));
        CPUGraph->setGeometry(QRect(10, 34, 695, 240));
        MemSwapGraph = new QCustomPlot(Resources_Tab);
        MemSwapGraph->setObjectName(QString::fromUtf8("MemSwapGraph"));
        MemSwapGraph->setGeometry(QRect(10, 315, 695, 150));
        label_14 = new QLabel(Resources_Tab);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 9, 81, 16));
        label_15 = new QLabel(Resources_Tab);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 290, 178, 16));
        NetworkGraph = new QCustomPlot(Resources_Tab);
        NetworkGraph->setObjectName(QString::fromUtf8("NetworkGraph"));
        NetworkGraph->setGeometry(QRect(10, 505, 695, 150));
        label_16 = new QLabel(Resources_Tab);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 480, 111, 16));
        tabWidget->addTab(Resources_Tab, QString());
        FileSystem_Tab = new QWidget();
        FileSystem_Tab->setObjectName(QString::fromUtf8("FileSystem_Tab"));
        verticalLayout = new QVBoxLayout(FileSystem_Tab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeWidget = new QTreeWidget(FileSystem_Tab);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setLineWidth(0);

        verticalLayout->addWidget(treeWidget);

        tabWidget->addTab(FileSystem_Tab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 735, 20));
        menuTask = new QMenu(menubar);
        menuTask->setObjectName(QString::fromUtf8("menuTask"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuTask->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuHelp->addSeparator();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Task Manager", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<b>Hardware</b>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<b>System Status</b>", nullptr));
        label_4->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "Memory:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Processor:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Available Disk Space:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<b>OS Information</b>", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(System_Tab), QCoreApplication::translate("MainWindow", "System", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_2->headerItem();
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("MainWindow", "Memory", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("MainWindow", "ID", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("MainWindow", "CPU", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "Status", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Name", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Processes_Tab), QCoreApplication::translate("MainWindow", "Processes", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "<b>CPU History</b>", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "<b>Memory and Swap History</b>", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "<b>Network History</b>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Resources_Tab), QCoreApplication::translate("MainWindow", "Resources", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->headerItem();
        ___qtreewidgetitem1->setText(6, QCoreApplication::translate("MainWindow", "Used", nullptr));
        ___qtreewidgetitem1->setText(5, QCoreApplication::translate("MainWindow", "Available", nullptr));
        ___qtreewidgetitem1->setText(4, QCoreApplication::translate("MainWindow", "Free", nullptr));
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("MainWindow", "Total", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("MainWindow", "Type", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("MainWindow", "Directory", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("MainWindow", "Device", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(FileSystem_Tab), QCoreApplication::translate("MainWindow", "File System", nullptr));
        menuTask->setTitle(QCoreApplication::translate("MainWindow", "Monitor", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
