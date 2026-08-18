#pragma once
#include "EnemyType.h"
#include "Room.h"

struct EnemyInfo
{
    EnemyType type;
    Room room;
    bool active;
};