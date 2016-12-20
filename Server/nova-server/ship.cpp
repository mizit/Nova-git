#include "ship.h"

Ship::Ship()
{
    pilotSocket = -1;
    navSocket = -1;
    engSocket = -1;
    batSocket = -1;
    login = QString("Name");
    password = QString("Password");
}
