#ifndef SHIP_H
#define SHIP_H

#include <QString>
#include <QPoint>

class CShellPosition
{
public:
    QPoint *pos;
    qint64 direction;
    qint64 speed;
    qint64 image_angle;
    qint64 rot_speed;
public:
    CShellPosition();
};

class CShell
{
public:
    CShellPosition* pos;
public:
    CShell();
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
    int *sockets[4];
    CShell *shell;
public:
    CShip();
};

#endif // SHIP_H
