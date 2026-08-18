#pragma once
#include "Room.h"

struct EnemyContext
{
    bool leftDoorClosed;
    bool rightDoorClosed;

    bool cctvOpen;
    Room selectedRoom;
};