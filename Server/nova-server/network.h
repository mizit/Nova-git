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
#include <casteroid.h>
#include <cbot.h>

#define NO      0
#define YES     1
#define BUSY    2
#define ERROR   3

#define NET_GOOD_DAY    1
#define NET_POSITION    2
#define NET_FIRST_LOAD  3
#define NET_IM_OUT      4
#define NET_MARK        5
#define NET_ITEM        6
#define NET_SHELL       7
#define NET_SHIP_DATA   8
#define NET_TEXT        9
#define NET_DOCK        10
#define NET_SUPPLIES    11
#define NET_SHOT        12
#define NET_TRADE       13
#define NET_ASTEROID    14
#define NET_BOT         15

#define PT_PILOT        1
#define PT_NAVIGATION   2
#define PT_ENGINEERING  3
#define PT_BATTLE       4

#define TX_MESSAGE      1
#define TX_SYSTEM       2

#define SP_HP_ADD       1
#define SP_HP_SUB       2
#define SP_OXYGEN_ADD   3
#define SP_OXYGEN_SUB   4


#define SPACE   "space"
#define IRL     "irl"

class MyServer : public QTcpServer
{
public:
    MyServer();
    void incomingConnection(qintptr);
};

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
qint64 GetInt64(unsigned char *str, int pos);
qint32 SetToRawData(unsigned char *str, int pos, qint32 data);
qint32 SetToRawData(unsigned char *str, int pos, qint64 data);
qint32 SetToRawData(unsigned char *str, int pos, QString data);
QString RawDataToString(char* data, int len);

void net_send_gd_answer(MySocket*, char);
void net_send_set_position(MySocket* socket, CShip* ship);
void net_send_mark(MySocket* socket, qint32 x, qint32 y);
void net_send_item(MySocket* socket, CItem* item, qint32 com);
void net_send_shell(MySocket* socket, CShell* shell);
void net_send_engine(MySocket* socket, CShip* ship);
void net_send_navigation(MySocket* socket, CShip* ship);
void net_send_text(MySocket* socket, QString str, qint32 flags, qint32 chn, qint32 distance);
void net_send_dock(MySocket* socket, CShip* ship1, CShip* ship2, qint32 flags);
void net_send_hp(MySocket* socket, CShip* ship);
void net_send_shot(MySocket* socket, SShot shot);
void net_send_asteroid(MySocket* socket, QList <CAsteroid*> asteroids);
void net_send_asteroid(MySocket* socket, CAsteroid* asteroids);
void net_send_bot(MySocket* socket, CBot* bot);
void net_send_damage(MySocket* socket, qint32 damage);


#endif // NETWORK_H
