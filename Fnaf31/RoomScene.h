#pragma once
#include "raylib.h"
#include "Room.h"
#include <vector>
#include "SceneLight.h"

struct RoomScene
{
    Room room{};

    Model model{};
    Camera3D camera{};

    Vector3 modelPosition{};
    float modelScale = 1.0f;

    std::vector<SceneLight> lights{};
};
