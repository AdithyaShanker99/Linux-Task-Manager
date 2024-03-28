#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

void FileSystemAddRoot(QString device, QString directory, QString type, QString total, QString free, QString available, QString used);
void BasicProcessInfo(QString name, QString status, QString cpu, QString id, QString memory);
//void OpenMapsFunc(QTreeWidgetItem*);
//void OpenFilesFunc(QTreeWidgetItem*);
//void OpenPropertiesFunc(QTreeWidgetItem*);
//void StopProcessFunc(QTreeWidgetItem*);
//void ContinueProcessFunc(QTreeWidgetItem*);
//void KillProcessFunc(QTreeWidgetItem*);

public slots:
//    void openMenu(QTreeWidgetItem * item, int column);
//    void slotCustomMenuRequested(QPoint pos);


    //void showContextMenu(const QPoint &pos);
    //void onContextMenuAction1();
    //void onContextMenuAction2();

private slots:
    //void on_treeWidget_2_customContextMenuRequested(const QPoint &pos);

    //void on_actionStop_hovered();

    //void on_actionkill_triggered();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double time;
    QTimer * my_timer;

private slots:
    void updateGraphs();
};
#endif // MAINWINDOW_H
