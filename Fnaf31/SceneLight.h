#pragma once
#include <string>
#include "raylib.h"
#include "cgltf.h"


enum class SceneLightType
{
    Directional,
    Point,
    Spot
};

struct SceneLight
{
    std::string name{};

    SceneLightType type = SceneLightType::Point;

    Vector3 position{};
    Vector3 direction{ 0.0f, 0.0f, -1.0f };

    Vector3 color{ 1.0f, 1.0f, 1.0f };

    float intensity = 1.0f;
    float range = 0.0f;

    float innerConeAngle = 0.0f;
    float outerConeAngle = PI / 4.0f;


};

