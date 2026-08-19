#pragma once
#include "raylib.h"
#include "EnemyType.h"

struct EnemyBillboardPose
{
    Room room{};
    Vector3 position{};
    float scale = 1.0f;
};

struct EnemyVisual
{
    EnemyType type{};
    Texture2D texture{};

    std::vector<EnemyBillboardPose> poses{};
};