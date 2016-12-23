#include "ship.h"

CShip::CShip()
{
    pilotSocket = -1;
    navSocket = -1;
    engSocket = -1;
    batSocket = -1;
    login = QString("Name");
    password = QString("Password");
    sockets[0] = &pilotSocket;
    sockets[1] = &navSocket;
    sockets[2] = &engSocket;
    sockets[3] = &batSocket;
    shell = new CShell();
}


CShellPosition::CShellPosition()
{
    pos = new QPoint();
    direction = 0;
    speed = 0;
    image_angle = 0;
    rot_speed = 0;
}

CShell::CShell()
{
    pos = new CShellPosition();
}
