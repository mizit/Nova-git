#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QStandardItem>
#include <mytablemodel.h>

#define NET_GOOD_DAY    1
#define NET_POSITION    2

#define PT_PILOT        1
#define PT_NAVIGATION   2
#define PT_ENGINEERING  3
#define PT_BATTLE       4


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

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QMap<int,QTcpSocket *> SClients;
    QStandardItemModel *log_model;
};

#endif // MAINWINDOW_H
