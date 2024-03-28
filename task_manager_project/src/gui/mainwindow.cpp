#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sysInfo.h"
#include "DirectoryStruct.h"
#include "cpuGraphs.h"
#include "memoryGraphs.h"
#include "network_monitor.h"
#include "system_info.h"
#include <iomanip>
#include <math.h>
#include <dirent.h>
#include <Processes.h>
#include "qcustomplot.h"
#include <iostream>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>

QT_CHARTS_USE_NAMESPACE


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    sysInfo system_info_1;

    system_info_1.parseSystemInfo();
    std::vector<std::string> input = getSystemInfo();
    SystemInfo system_info_2 = parseSystemInfo(input);
    std::vector<Directory> result = executeAndParseDf();

    this->setFixedSize(735, 765);

    //Systems Tab
    ui->setupUi(this);
    ui->label_10->setText("OS Release Verison:"+QString::fromStdString(system_info_2.operatingSystem));
    ui->label_11->setText("Kernal Version:" + QString::fromStdString(system_info_2.kernel + system_info_2.architecture));
    ui->label_7->setText(QString::fromStdString(system_info_1.totalMemory));
    ui->label_8->setText(QString::fromStdString(system_info_1.processorVersion));
    ui->label_12->setText(QString::fromStdString(result[result.size() - 1].avail));
    result.erase(result.begin() + result.size() - 1);

    //Proccess Tab

    //Resources Tab

    //CPU Graph
    //Adding graph and setting colors
    std::vector<double> CPUData = CPUGraphs::executeMPStatAndParse();
    for(int i = 1; i < (int)CPUData.size(); i++) {
        ui->CPUGraph->addGraph();
        QPen pen;
        pen.setWidth(2);
        pen.setColor(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
        ui->CPUGraph->graph(i - 1)->setPen(pen);
        ui->CPUGraph->graph(i - 1)->setName(QString::fromStdString("CPU" + std::to_string(i)+ ": " + std::to_string(CPUData[i]) + "%"));
        ui->CPUGraph->graph(i - 1)->removeFromLegend();
        ui->CPUGraph->graph(i - 1)->addToLegend();

    }

    //Seting axes
    ui->CPUGraph->graph(0)->data();
    ui->CPUGraph->xAxis->setLabel("Time");
    ui->CPUGraph->xAxis->setRange(0, 60);
    ui->CPUGraph->yAxis->setLabel("Pecent");
    ui->CPUGraph->yAxis->setRange(0, 100);
    ui->CPUGraph->legend->setVisible(true);
    ui->CPUGraph->axisRect()->setAutoMargins(QCP::msLeft | QCP::msTop | QCP::msBottom);
    ui->CPUGraph->axisRect()->setMargins(QMargins(0,0,190,0));
    ui->CPUGraph->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
    ui->CPUGraph->axisRect()->insetLayout()->setInsetRect(0, QRectF(1.05,0,0.4,1.1));

    //Memory and Swap History
    //Adding graph and setting colors
    ui->MemSwapGraph->addGraph();
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(255, 0, 255));
    ui->MemSwapGraph->graph(0)->setPen(pen);
    ui->MemSwapGraph->graph(0)->setName(QString::fromStdString("Memory: --%"));
    ui->MemSwapGraph->addGraph();
    ui->MemSwapGraph->graph(0)->removeFromLegend();
    ui->MemSwapGraph->graph(0)->addToLegend();
    pen.setWidth(2);
    pen.setColor(QColor(0, 255, 0));
    ui->MemSwapGraph->graph(1)->setPen(pen);
    ui->MemSwapGraph->graph(1)->setName(QString::fromStdString("Swap: --%"));
    ui->MemSwapGraph->graph(1)->removeFromLegend();
    ui->MemSwapGraph->graph(1)->addToLegend();

    //Seting axes
    ui->MemSwapGraph->xAxis->setLabel("Time");
    ui->MemSwapGraph->xAxis->setRange(0, 60);
    ui->MemSwapGraph->yAxis->setLabel("Pecent");
    ui->MemSwapGraph->yAxis->setRange(0, 100);
    ui->MemSwapGraph->legend->setVisible(true);
    ui->MemSwapGraph->axisRect()->setAutoMargins(QCP::msLeft | QCP::msTop | QCP::msBottom);
    ui->MemSwapGraph->axisRect()->setMargins(QMargins(0,0,200,0));
    ui->MemSwapGraph->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
    ui->MemSwapGraph->axisRect()->insetLayout()->setInsetRect(0, QRectF(1.05,0,0.1,1.1));


    //Memory and Swap History
    //Adding graph and setting colors
    ui->NetworkGraph->addGraph();
    pen.setWidth(2);
    pen.setColor(QColor(0, 0, 255));
    ui->NetworkGraph->graph(0)->setPen(pen);
    ui->NetworkGraph->graph(0)->setName(QString::fromStdString("Recieving: --KiB/s"));
    ui->NetworkGraph->graph(0)->removeFromLegend();
    ui->NetworkGraph->graph(0)->addToLegend();
    ui->NetworkGraph->addGraph();
    pen.setWidth(2);
    pen.setColor(QColor(255, 0, 0));
    ui->NetworkGraph->graph(1)->setPen(pen);
    ui->NetworkGraph->graph(1)->setName(QString::fromStdString("Sending: --KiB/s"));
    ui->NetworkGraph->graph(1)->removeFromLegend();
    ui->NetworkGraph->graph(1)->addToLegend();

    //Seting axes
    ui->NetworkGraph->xAxis->setLabel("Time");
    ui->NetworkGraph->xAxis->setRange(0, 60);
    ui->NetworkGraph->yAxis->setLabel("KiB/s");
    ui->NetworkGraph->yAxis->setRange(0, 100);
    ui->NetworkGraph->legend->setVisible(true);
    ui->NetworkGraph->axisRect()->setAutoMargins(QCP::msLeft | QCP::msTop | QCP::msBottom);
    ui->NetworkGraph->axisRect()->setMargins(QMargins(0,0,220,0));
    ui->NetworkGraph->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
    ui->NetworkGraph->axisRect()->insetLayout()->setInsetRect(0, QRectF(1.05,0,0.1,1.1));


    time = 0.0;

    //test
    my_timer = new QTimer(this);
    connect(my_timer, &QTimer::timeout, this, &MainWindow::updateGraphs);
    my_timer->start(250);

     DIR * dir;
    struct dirent * entry;
    dir = opendir("/proc");
    if (dir == NULL) {
     perror("opendir");
     exit(EXIT_FAILURE);
    }
    std::vector<processInfo> processes;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0) {
            processInfo process;
            process.getProcessInfo(entry->d_name, process);
            //std::cout << process.memory << '\n';
            processes.push_back(process);
            QString name = QString::fromStdString(process.name);
            QString status = QString::fromStdString(process.status);
            QString cpu = QString::fromStdString(process.cpuPercent);
            QString id = QString::fromStdString(process.pid);
            QString memory = QString::fromStdString(process.virtualMem);
            BasicProcessInfo(name, status, cpu, id, memory);
        }
    }
    closedir(dir);
//    connect(ui->treeWidget_2,SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(openMenu(QTreeWidgetItem *, int)));


//    QAction* stopProcess = new QAction(tr("Stop Process"), ui->treeWidget_2);
//    QAction* killProcess = new QAction(tr("Kill Process"), ui->treeWidget_2);
//    QAction* continueProcess = new QAction(tr("Continue Process"), ui->treeWidget_2);
//    QAction* openFile = new QAction(tr("Open Files"), ui->treeWidget_2);
//    QAction* properties = new QAction(tr("Properties"), ui->treeWidget_2);
//    QAction* openMaps = new QAction(tr("Open Mem Maps"), ui->treeWidget_2);

//    ui->treeWidget_2->setContextMenuPolicy(Qt::ActionsContextMenu);
//    ui->treeWidget_2->addAction(openMaps);
//    ui->treeWidget_2->addAction(stopProcess);
//    ui->treeWidget_2->addAction(killProcess);
//    ui->treeWidget_2->addAction(continueProcess);
//    ui->treeWidget_2->addAction(properties);
//    ui->treeWidget_2->addAction(openFile);

//    connect(openMaps, &QAction::triggered, this, [this]() { OpenMapsFunc(ui->treeWidget_2->currentItem()); });
//    connect(properties, &QAction::triggered, this, [this]() { OpenPropertiesFunc(ui->treeWidget_2->currentItem()); });
//    connect(stopProcess, &QAction::triggered, this, [this]() { StopProcessFunc(ui->treeWidget_2->currentItem()); });
//    connect(killProcess, &QAction::triggered, this, [this]() { KillProcessFunc(ui->treeWidget_2->currentItem()); });
//    connect(continueProcess, &QAction::triggered, this, [this]() { ContinueProcessFunc(ui->treeWidget_2->currentItem()); });
//    connect(openFile, &QAction::triggered, this, [this]() { OpenFilesFunc(ui->treeWidget_2->currentItem()); });
//    connect(ui->treeWidget_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

//for (int i = 0, i < processes.size(); i++ ) {

    //}


    //File System Tab
    for (const auto& dir : result) {

        QString device = QString::fromStdString(dir.filesystem);
        QString directory = QString::fromStdString(dir.mountedOn);
        QString type = QString::fromStdString(dir.type);
        QString total = QString::fromStdString(dir.size);
        std::string tmp_free = std::to_string((std::roundf(std::stof(dir.size.substr(0, dir.size.size() - 1)) * (1 - std::stof(dir.usePercentage.substr(0, dir.usePercentage.size() - 1))/100) * 10) / 10));
        QString free = QString::fromStdString(tmp_free.substr(0, tmp_free.size() - 5) + dir.size.substr(dir.size.size() - 1));
        QString available = QString::fromStdString(dir.avail);
        QString used = QString::fromStdString(dir.used);

        //, QString directory, QString type, QString total, QString free, QString available, QString used
        FileSystemAddRoot(device, directory, type, total, free, available, used);
    }

}

void MainWindow::FileSystemAddRoot(QString device, QString directory, QString type, QString total, QString free, QString available, QString used){
    QTreeWidgetItem *itm = new QTreeWidgetItem(false);
    itm->setText(0, device);
    itm->setText(1, directory);
    itm->setText(2, type);
    itm->setText(3, total);
    itm->setText(4, free);
    itm->setText(5, available);
    itm->setText(6, used);
    ui->treeWidget->addTopLevelItem(itm);
}

void MainWindow::updateGraphs() {
    NetworkMonitor networkMonitor("eth0:");
    std::vector<double> CPUData = CPUGraphs::executeMPStatAndParse();
    std::array<double, 2> MemSwapData = MemoryGraphs::executeCommandAndParse();
    std::vector<double> NetworkData = networkMonitor.getNetworkRates();

    if(time > 60) {
        ui->CPUGraph->xAxis->setRange(time - 60, time + 10);
        ui->NetworkGraph->xAxis->setRange(time - 60, time + 10);
        ui->MemSwapGraph->xAxis->setRange(time - 60, time + 10);
    }

    for (int i = 1; i < (int)CPUData.size(); i++) {
        ui->CPUGraph->graph(i - 1)->addData(time, CPUData[i]);
        ui->CPUGraph->graph(i - 1)->setName(QString::fromStdString("CPU" + std::to_string(i)+ ": " + std::to_string(CPUData[i]) + "%"));
    }

    ui->NetworkGraph->graph(0)->addData(time, NetworkData[0]);
    ui->NetworkGraph->graph(0)->setName(QString::fromStdString("Receiving: "+ std::to_string(NetworkData[0]) +"KiB/S"));
    ui->NetworkGraph->graph(1)->addData(time, NetworkData[1]);
    ui->NetworkGraph->graph(1)->setName(QString::fromStdString("Sending: "+ std::to_string(NetworkData[1]) +"KiB/S"));


    ui->MemSwapGraph->graph(0)->addData(time, MemSwapData[0]);
    ui->MemSwapGraph->graph(0)->setName(QString::fromStdString("Memory: "+ std::to_string(MemSwapData[0]) +"%"));
    ui->MemSwapGraph->graph(1)->addData(time, MemSwapData[1]);
    ui->MemSwapGraph->graph(1)->setName(QString::fromStdString("Swap: " + std::to_string(MemSwapData[1])  + "%"));

    ui->NetworkGraph->replot();
    ui->CPUGraph->replot();
    ui->MemSwapGraph->replot();
    time += 1;

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::openMenu(QTreeWidgetItem * item, int column) {



//}
//void MainWindow::OpenMapsFunc(QTreeWidgetItem * item) {
//    QString pid = item->text(4);
//    std::cout << pid.toStdString() << '\n';
//    DialogTest dialogtest;
//    dialogtest.setModal(true);
//    dialogtest.exec();

//}

//void MainWindow::OpenPropertiesFunc(QTreeWidgetItem * item) {
//    QString pid = item->text(4);
//    std::cout << pid.toStdString() << '\n';
//    DialogTest dialogtest;
//    dialogtest.setModal(true);
//    dialogtest.exec();

//}

//void MainWindow::KillProcessFunc(QTreeWidgetItem * item) {
//    QString pid = item->text(4);
//    std::cout << pid.toStdString() << '\n';
//    DialogTest dialogtest;
//    dialogtest.setModal(true);
//    dialogtest.exec();

//}

//void MainWindow::StopProcessFunc(QTreeWidgetItem * item) {
//    QString pid = item->text(4);
//    std::cout << pid.toStdString() << '\n';
//    DialogTest dialogtest;
//    dialogtest.setModal(true);
//    dialogtest.exec();

//}
//void MainWindow::ContinueProcessFunc(QTreeWidgetItem * item) {
//    QString pid = item->text(4);
//    std::cout << pid.toStdString() << '\n';
//    DialogTest dialogtest;
//    dialogtest.setModal(true);
//    dialogtest.exec();

//}
//void MainWindow::OpenFilesFunc(QTreeWidgetItem * item) {
//    QString pid = item->text(4);
//    std::cout << pid.toStdString() << '\n';
//    DialogTest dialogtest;
//    dialogtest.setModal(true);
//    dialogtest.exec();

//}


//void MainWindow::FileSystemAddRoot(QString device, QString directory, QString type, QString total, QString free, QString available, QString used){
//    QTreeWidgetItem *itm = new QTreeWidgetItem(false);
//    itm->setText(0, device);
//    itm->setText(1, directory);
//    itm->setText(2, type);
//    itm->setText(3, total);
//    itm->setText(4, free);
//    itm->setText(5, available);
//    itm->setText(6, used);
//    ui->treeWidget->addTopLevelItem(itm);
//}
void MainWindow::BasicProcessInfo(QString name, QString status, QString cpu, QString id, QString memory){
    QTreeWidgetItem *itm = new QTreeWidgetItem(false);
    itm->setText(0, name);
    itm->setText(1, status);
    itm->setText(2, cpu);
    itm->setText(3, id);
    itm->setText(4, memory);
    //itm->setText(5, available);
    //itm->setText(6, used);
    //connect(ui->treeWidget_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    ui->treeWidget_2->addTopLevelItem(itm);

}

