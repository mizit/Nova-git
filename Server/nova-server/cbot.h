#ifndef CBOT_H
#define CBOT_H

#include <QString>
#include <QPoint>
#include <QList>
#include <QTimer>
#include <citem.h>
#include <ship.h>
//#include <network.h>
#include <QObject>
#include <QListWidget>
#include <QLineEdit>
#include <math.h>

#define HIPER_MIND  0
#define MINER       1
#define CARRYALL    2
#define ANOMALY     3
#define FINDER      4

#define BC_RETURN   1
#define BC_GO       2
#define BC_ATTACK   3
#define BC_DROP     4

class CBot;
class CHyperMind;
class CBotCommand;
class CBotTimer;

class CBotCommand
{
public:
    CBotCommand();
    void GoToBoss();
    void GoToCoordinate(qint64 x, qint64 y);
    void Drop(CBot* bot);
    void Drop(CItem* item);
    void GoToShip(CShip* goal);
public:
    qint32 type;
    qint32 x;
    qint32 y;
    CShip* goal;
    CBot* owner;
    CBot* bot_to_drop;
    CItem* item_to_drop;
};

class CBot : public QObject
{
    Q_OBJECT

public:
    CBot();
    void setActive(qint8 active);
    ~CBot();

public slots:
    void ExecuteCommand();
    void Update();

signals:
    void GonnaDead();

public:
    qint32 net_id;
    qint32 hp;
    double speed;
    qint32 max_speed;
    double direction;
    qint32 vspeed;
    qint32 hspeed;
    qint32 type;
    double x;
    double y;
    qint32 active;
    CHyperMind* boss;
    QList <CItem*> item_list;
    QList <CBot*> cargo_bots;
    QList <CBotCommand*> commands_list;
    CBotTimer* timer;
    CBotTimer* update_timer;
    qint32 time_update;
    QListWidget* my_commands;
    QListWidget* my_inventory;
    QString name;
    qint32 ready_to_send;
};

class CMiner:public CBot
{
public:
    CMiner();
};

class CCarryall:public CBot
{
public:
    CCarryall();
};

class CAnomaly:public CBot
{
public:
    CAnomaly();
};

class CFinder:public CBot
{
public:
    CFinder();
};

class CHyperMind:public CBot
{
    Q_OBJECT

public:
    CHyperMind();
    void BotCreate(qint32 type, qint8 active);
    void CargoLoad(CBot* bot);
    void CargoLoad(CItem* item);
    void ChangeData();

public slots:
    void BotDead();
    void MinerCreate();
    void CarryallCreate();
    void AnomalyCreate();
    void FinderCreate();
    void ComAddBack();
    void ComAddGo();
    void ComAddDrop();
    void ComAddAttack();

public:
    QList <CBot*> bots;
    QList <CCarryall*> carryalls;
    qint32 hp_add;
    QList <qint32> id_list;
    QList <CShip*> ship_list;
    QListWidget *my_bots;
    QListWidget *items_view;
    QList <CItem*> *space_list;
    QLineEdit* comx;
    QLineEdit* comy;
};

class CBotTimer : public QTimer
{
public:
    CBotTimer();
public:
    CBot* owner;
};

#endif // CBOT_H
