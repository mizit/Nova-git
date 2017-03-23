#ifndef SHIP_H
#define SHIP_H

#include <QString>
#include <QPoint>
#include <citem.h>
#include <QSettings>

#define PM_TUBE     0x01
#define PM_POWER    0x02
#define PM_NAV      0x04
#define PM_ENGINE   0x08
#define PM_WEAPON   0x10
#define PM_LS       0x20

#define GRID_SIZE   7

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
    qint32 air_output;
    qint32 air_bank;
    qint32 safely;
    qint32 radar_range;
    qint32 radio_range;
    qint32 system_level;
    qint32 main_drive;
    qint32 man_drive;
    qint32 back_drive;
    qint32 mass;
    QList <CWeapon*> weapons;
public:
    CShip();
};

#endif // SHIP_H
