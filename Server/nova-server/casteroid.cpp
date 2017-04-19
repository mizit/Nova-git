#include "casteroid.h"

CAsteroid::CAsteroid()
{

}

void CAsteroid::setType(qint32 tp)
{
    code = tp;
    switch (code)
    {
    case 0:
        type = GOLD;
        break;
    case 1:
        type = RUBY;
        break;
    case 2:
        type = EMERALD;
        break;
    }
}


CDevourer::CDevourer()
{
    timer = new CDevourerTimer();
    timer->owner = this;
}

CDevourer::~CDevourer()
{
    delete timer;
}

CAsteroid* CDevourer::FindNearestAsteroid(QList <CAsteroid*> asteroids)
{
    qint64 min = 10000000;
    CAsteroid* astr;
    for (int i = 0; i < asteroids.size(); i++)
    {
        qint64 tmp = point_distance(base->pos, asteroids[i]->x, asteroids[i]->y);
        if (min > tmp)
        {
            min = tmp;
            astr = asteroids[i];
        }
    }
    return astr;
}

bool CDevourer::CanDig()
{
    if (point_distance(base->pos, nearest_asteroid->x, nearest_asteroid->y) < 500)
    {
        return true;
    }
    else
    {
        return false;
    }
}

CDevourerTimer::CDevourerTimer()
{

}
