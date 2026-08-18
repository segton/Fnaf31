#pragma once

enum class Room
{
    MainStage,
    FoodCourt,
    GameStalls,
    MainHall,
    LeftHall,
    RightHall,
    LeftDoor,
    RightDoor
};


const char* roomName(Room room);

