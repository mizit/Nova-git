#ifndef SHIP_H
#define SHIP_H

#include <QString>
#include <QPoint>
#include <citem.h>
#include <QSettings>
#include <QLineEdit>
#include <QValidator>

#define PM_TUBE     0x01
#define PM_POWER    0x02
#define PM_NAV      0x04
#define PM_ENGINE   0x08
#define PM_WEAPON   0x10
#define PM_LS       0x20

#define GRID_SIZE   7

#define NUM_ATR         17

#define BN_AIR_OUTPUT   0
#define BN_AIR_BANK     1
#define BN_SAFELY       2
#define BN_RADAR_RANGE  3
#define BN_RADIO_RANGE  4
#define BN_SYSTEM_LEVEL 5
#define BN_MAIN_DRIVE   6
#define BN_MAN_DRIVE    7
#define BN_BACK_DRIVE   8
#define BN_MASS         9
#define BN_WEAPON_STR   10
#define BN_WEAPON_RANGE 11
#define BN_WEAPON_RAPID 12
#define BN_MAX_HP       13
#define BN_MAX_OXYGEN   14
#define BN_HP           15
#define BN_OXYGEN       16

struct SShot
{
    qint32 x;
    qint32 y;
    qint32 speed;
    qint32 direction;
    qint32 damage;
    qint32 ttl;
};

class CAttribute
{
public:
    CAttribute();
    qint32 Calculation();
    void setOutput(QLineEdit*);
    void setInput(QLineEdit*);
    void ClearEdit();
public:
    qint32 base;
    qint32 bonus;
    qint32 max;
    qint32 min;
    qint32 result;
    QLineEdit* output;
    QLineEdit* input_bonus;
    QIntValidator* validator;
    QString name;
};

class CWeapon
{
public:
    CWeapon();
public:
    qint32 weapon;
    qint32 shields;
    qint32 electronic_warfare;
};

class CShellPosition
{
public:
    QPoint *pos;
    qint32 direction;
    qint32 speed;
    qint32 image_angle;
    qint32 rot_speed;
public:
    CShellPosition();
};

class CCell
{
public:
    CCell();
public:
    int permissions;
};

class CShell
{
public:
    QString name;
    CCell grid[GRID_SIZE][GRID_SIZE];
    CShellPosition* pos;
public:
    CShell();
    void loadgrid();
};

class CShip
{
public:
    int pilotSocket;
    int navSocket;
    int engSocket;
    int batSocket;
    QString login;
    QString password;
    int *sockets[5];
    CShell *shell;
    QList <CItem*> item_list;
    CAttribute attribute[NUM_ATR];
public:
    CShip();
};

qint64 point_distance(QPoint* point1, QPoint* point2);
qint64 point_distance(QPoint point1, qint32 x, qint32 y);
qint64 point_distance(qint32 x1, qint32 y1, qint32 x2, qint32 y2);
qint32 min(qint32 a1, qint32 a2);

#endif // SHIP_H
