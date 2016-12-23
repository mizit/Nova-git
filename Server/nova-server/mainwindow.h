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
    QString RawDataToString(char* data, int len);

private slots:
    void newUser();
    void slotReadClient();
    void UserCreate();
    void DataUpdate();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QMap<int,QTcpSocket *> SClients;
    QStandardItemModel *log_model;
    MyTableModel *table_model;
    QTimer *timer_update;
};

QString GetString(char *, int pos);
qint32 GetInt32(unsigned char *str, int pos);


#endif // MAINWINDOW_H
