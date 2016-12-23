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

void net_send_gd_answer(QTcpSocket*, char);



#endif // NETWORK_H
