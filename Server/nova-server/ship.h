#ifndef SHIP_H
#define SHIP_H

#include <QString>

class Ship
{
public:
    int pilotSocket;
    int navSocket;
    int engSocket;
    int batSocket;
    QString login;
    QString password;
public:
    Ship();
};

#endif // SHIP_H
