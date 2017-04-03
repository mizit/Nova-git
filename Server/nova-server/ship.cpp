#include "ship.h"

CWeapon::CWeapon()
{
    weapon = 0;
    shields = 0;
    electronic_warfare = 0;
}

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
    air_output = 0;
    air_bank = 0;
    safely = 0;
    radar_range = 0;
    radio_range = 0;
    system_level = 0;
    main_drive = 0;
    man_drive = 0;
    back_drive = 0;
    mass = 0;
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

qint64 point_distance(QPoint* point1, QPoint* point2)
{
    qint64 x1 = point1->rx() / 1000;
    qint64 x2 = point2->rx() / 1000;
    qint64 y1 = point1->ry() / 1000;
    qint64 y2 = point2->ry() / 1000;
    return static_cast <qint64> (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}
