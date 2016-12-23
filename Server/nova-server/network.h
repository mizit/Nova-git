#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QWidget>
#include <QVariant>
#include <ship.h>
#include <QList>
#include <QTcpServer>
#include <QTcpSocket>

#define NO      0
#define YES     1
#define BUSY    2
#define ERROR   3

#define NET_GOOD_DAY    1
#define NET_POSITION    2

#define PT_PILOT        1
#define PT_NAVIGATION   2
#define PT_ENGINEERING  3
#define PT_BATTLE       4


class MySocket : public QTcpSocket
{
public:
    CShip *parentShip;
    int pt_type;
public:
    MySocket();
};

QString GetString(char *, int pos);
qint32 GetInt32(unsigned char *str, int pos);
qint32 SetToRawData(unsigned char *str, int pos, qint32 data);
qint32 SetToRawData(unsigned char *str, int pos, QString data);

void net_send_gd_answer(QTcpSocket*, char);
void net_send_set_position(QTcpSocket* socket, CShip* ship);

#endif // NETWORK_H
