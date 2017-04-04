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

class CAtribute
{
public:
    CAtribute();
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
    CAtribute air_output;
    CAtribute air_bank;
    CAtribute safely;
    CAtribute radar_range;
    CAtribute radio_range;
    CAtribute system_level;
    CAtribute main_drive;
    CAtribute man_drive;
    CAtribute back_drive;
    CAtribute mass;
    QList <CWeapon*> weapons;
    CAtribute max_hp;
    CAtribute max_oxygen;
    CAtribute hp;
    CAtribute oxygen;
public:
    CShip();
};

qint64 point_distance(QPoint* point1, QPoint* point2);

#endif // SHIP_H
