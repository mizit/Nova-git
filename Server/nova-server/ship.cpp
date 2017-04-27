#include "ship.h"

CAttribute::CAttribute()
{
    base = 0;
    bonus = 0;
    max = 1000000;
    min = 1;
    result = 0;
    output = 0;
    input_bonus = 0;
    validator = new QIntValidator(-max, max);
    name = "";
};

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
    attribute[BN_SAFELY].min = 0;
    attribute[BN_SYSTEM_LEVEL].min = 0;
    attribute[BN_WEAPON_STR].min = 0;
    attribute[BN_AIR_BANK].min = 0;
    attribute[BN_MAIN_DRIVE].min = 0;
    attribute[BN_MAN_DRIVE].min = 0;
    attribute[BN_AIR_OUTPUT].name = "air_output";
    attribute[BN_AIR_BANK].name = "air_bank";
    attribute[BN_SAFELY].name = "safely";
    attribute[BN_RADAR_RANGE].name = "radar_range";
    attribute[BN_RADIO_RANGE].name = "radio_range";
    attribute[BN_SYSTEM_LEVEL].name = "system_level";
    attribute[BN_MAIN_DRIVE].name = "main_drive";
    attribute[BN_MAN_DRIVE].name = "man_drive";
    attribute[BN_BACK_DRIVE].name = "back_drive";
    attribute[BN_MASS].name = "mass";
    attribute[BN_WEAPON_STR].name = "weapon_str";
    attribute[BN_WEAPON_RANGE].name = "weapon_range";
    attribute[BN_WEAPON_RAPID].name = "weapon_rapid";
    attribute[BN_MAX_HP].name = "max_hp";
    attribute[BN_MAX_OXYGEN].name = "max_oxygen";
    attribute[BN_HP].name = "hp";
    attribute[BN_OXYGEN].name = "oxygen";

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

qint64 point_distance(QPoint point1, qint32 x, qint32 y)
{
    qint64 x1 = point1.rx() / 1000;
    qint64 x2 = x * 100;
    qint64 y1 = point1.ry() / 1000;
    qint64 y2 = y * 100;
    return static_cast <qint64> (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

qint64 point_distance(qint32 X1, qint32 Y1, qint32 X2, qint32 Y2)
{
    qint64 x1 = X1;
    qint64 x2 = X2;
    qint64 y1 = Y1;
    qint64 y2 = Y2;
    return static_cast <qint64> (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

qint32 min(qint32 a1, qint32 a2)
{
    if (a1 < a2)
        return a1;
    else
        return a2;
}

double point_direction(qint32 x1, qint32 y1, qint32 x2, qint32 y2)
{
    double additional = 0;
    double x, y;
    x = x2 - x1;
    y = y2 - y1;
    if ((x >= 0) && (y >= 0))
    {
        additional = 0;
    }
    else if ((x <= 0) && (y >= 0))
    {
        additional = M_PI / 2;
    }
    else if ((x <= 0) && (y <= 0))
    {
        additional = M_PI;
    }
    else if ((x >= 0) && (y <= 0))
    {
        additional = 3 * M_PI / 2;
    }
    double ans = (double)atan((double)abs(y)/(double)abs(x)) + additional;
    return ans;
}

qint32 CAttribute::Calculation()
{
    if (input_bonus > 0)
    {
        bonus = input_bonus->text().toInt();
    }
    result = base + bonus;
    if (result > max)
        result = max;
    if (result < min)
        result = min;
    if (output > 0)
    {
        output->setText(QString("%1").arg(result));
    }
    return result;
}

void CAttribute::setInput(QLineEdit * edit)
{
    edit->setValidator(validator);
    input_bonus = edit;
    input_bonus->setText(QString("%1").arg(bonus));
}

void CAttribute::setOutput(QLineEdit * edit)
{
    edit->setValidator(validator);
    output = edit;
}

void CAttribute::ClearEdit()
{
    input_bonus = 0;
    output = 0;
}
