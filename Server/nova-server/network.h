#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QWidget>
#include <QVariant>
#include <ship.h>
#include <QList>
#include <QListView>
#include <QTcpServer>
#include <QTcpSocket>
#include <QStandardItem>

#define NO      0
#define YES     1
#define BUSY    2
#define ERROR   3

#define NET_GOOD_DAY    1
#define NET_POSITION    2
#define NET_FIRST_LOAD  3
#define NET_IM_OUT      4
#define NET_MARK        5

#define PT_PILOT        1
#define PT_NAVIGATION   2
#define PT_ENGINEERING  3
#define PT_BATTLE       4


class MySocket : public QTcpSocket
{
public:
    CShip *parentShip;
    int pt_type;
    int descriptor;
    QListView *log;
    QStandardItemModel *log_model;
public:
    MySocket();
    qint64 MyWrite(char* data, quint64 maxSize);
    void LogAddString(QString str);
};

QString GetString(char *, int pos);
qint32 GetInt32(unsigned char *str, int pos);
qint32 SetToRawData(unsigned char *str, int pos, qint32 data);
qint32 SetToRawData(unsigned char *str, int pos, QString data);
QString RawDataToString(char* data, int len);

void net_send_gd_answer(MySocket*, char);
void net_send_set_position(MySocket* socket, CShip* ship);
void net_send_mark(MySocket* socket, qint32 x, qint32 y);

#endif // NETWORK_H
