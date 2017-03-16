#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QStandardItem>
#include <mytablemodel.h>
#include <QSettings>
#include <network.h>
#include <QTimer>
#include <citem.h>
#include <QVariant>
#include <QFile>

#define SHIPS   table_model->ship_list

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void LogAddString(QString str);

private slots:
    void newUser();
    void slotReadClient();
    void UserCreate();
    void DataUpdate();
    void DataSave();
    void UserDisconnected();
    void pbtn();
    void LockPos();
    void SetPos();
    void ItemAdd();

private:
    Ui::MainWindow *ui;
    MyServer *server;
    QMap<int, MySocket*> SClients;
    MyTableModel *table_model;
    QStandardItemModel *log_model;
    QTimer *timer_update;
    QTimer *timer_save;
    CIdGen *idgen;
    QList <CItem*> space_items;
};



#endif // MAINWINDOW_H
