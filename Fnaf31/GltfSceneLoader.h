#pragma once

#include <string>
#include <vector>

#include "SceneLight.h"

class GltfSceneLoader
{
public:
    static std::vector<SceneLight> loadLights(const std::string& path);
};