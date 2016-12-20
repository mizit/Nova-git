#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    log_model = new QStandardItemModel;
    ui->log->setModel(log_model);

    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newUser()));
    server->listen(QHostAddress::Any, 63258);  

    //table_model = new QAbstractTableModel;
    MyTableModel *table_model = new MyTableModel();
    ui->tableView->setModel(table_model);
    table_model->add_ship(Ship());


}

void MainWindow::newUser()
{
    QTcpSocket* clientSocket;
    clientSocket = server->nextPendingConnection();
    int idusersocs = clientSocket->socketDescriptor();
    SClients[idusersocs]=clientSocket;
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

}

void MainWindow::slotReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    char *data;
    char tmp_len[2];
    int len;
    QDataStream net_data(clientSocket);
    net_data.readRawData(tmp_len, 2);
    len = (tmp_len[1] << 8) + tmp_len[0];
    data = new char[len];
    net_data.readRawData(data, len);
    //LogAddString(RawDataToString(data, len));
    switch (data[0])
    {
        case NET_GOOD_DAY:

        break;
    }
}

MainWindow::~MainWindow()
{
    foreach(int i,SClients.keys())
    {
        SClients[i]->close();
        SClients.remove(i);
    }
    server->close();

    delete ui;
}

QString MainWindow::RawDataToString(char* data, int len)
{
    QString str;
    str = QString("NET << ");
    for (int i = 0; i < len; i++)
    {
        str += QString("0x%1 ").arg(int(data[i]), 2, 16, QChar('0'));
    }
    return str;
}

void MainWindow::LogAddString(QString str)
{
    QStandardItem *item;
    item = new QStandardItem();
    item->setText(str);
    log_model->appendRow(item);
    ui->log->scrollToBottom();
}
