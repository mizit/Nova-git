#ifndef CASTEROID_H
#define CASTEROID_H

#include <QString>
#include <QPoint>
#include <QList>
#include <QTimer>
#include <citem.h>
#include <ship.h>

class CDevourer;
class CDevourerTimer;

class CAsteroid
{
public:
    CAsteroid();
    void setType(qint32);
public:
    qint32 x;
    qint32 y;
    qint32 code;
    QString type;
    qint32 num;
};

class CDevourer
{
public:
    CDevourer();
    CAsteroid* FindNearestAsteroid(QList <CAsteroid*> asteroids);
    bool CanDig();
    ~CDevourer();
public:
    CDevourerTimer *timer;
    CAsteroid *nearest_asteroid;
    CItem *base;
    qint32 devour_time;
};

class CDevourerTimer : public QTimer
{
public:
    CDevourerTimer();
public:
    CDevourer* owner;
};

#endif // CASTEROID_H
