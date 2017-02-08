#include "ship.h"

CShip::CShip()
{
    pilotSocket = -1;
    navSocket = -1;
    engSocket = -1;
    batSocket = -1;
    login = QString("Name");
    password = QString("Password");
    sockets[0] = 0;
    sockets[1] = &pilotSocket;
    sockets[2] = &navSocket;
    sockets[3] = &engSocket;
    sockets[4] = &batSocket;
    shell = new CShell();
}

void CShell::loadgrid()
{
    QSettings sett("data/ships.ini", QSettings::IniFormat);
    sett.beginGroup(name);
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j].permissions = sett.value(QString("%1x%2").arg(i).arg(j)).toFloat();
        }
    }
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

CCell::CCell()
{

}
