#include "GltfSceneLoader.h"

#include "cgltf.h"

#include "raylib.h"
#include "raymath.h"

#include <iostream>

std::vector<SceneLight> GltfSceneLoader::loadLights(const std::string& path)
{
    std::vector<SceneLight> lights{};

    cgltf_options options{};
    cgltf_data* data = nullptr;

    const cgltf_result result =
        cgltf_parse_file(
            &options,
            path.c_str(),
            &data
        );

    std::cout << "[GLTF] Nodes: "
        << data->nodes_count
        << '\n';

    std::cout << "[GLTF] Light definitions: "
        << data->lights_count
        << '\n';

    std::cout << "[GLTF] Extensions used: "
        << data->extensions_used_count
        << '\n';

    for (cgltf_size i = 0; i < data->extensions_used_count; ++i)
    {
        std::cout << "    "
            << data->extensions_used[i]
            << '\n';
    }

    if (result != cgltf_result_success)
    {
        std::cout << "Failed to parse GLB: " << path << '\n';

        return lights;
    }

    // Read lights here.
    for (cgltf_size i = 0; i < data->nodes_count; ++i)
    {
        const cgltf_node& node = data->nodes[i];

        if (node.light == nullptr)
        {
            continue;
        }

        const cgltf_light& gltfLight = *node.light;

        SceneLight light{};

        light.name =
            node.name != nullptr
            ? node.name
            : "Unnamed Light";

        light.color = {
            gltfLight.color[0],
            gltfLight.color[1],
            gltfLight.color[2]
        };

        light.intensity = gltfLight.intensity;
        light.range = gltfLight.range;

        light.innerConeAngle =
            gltfLight.spot_inner_cone_angle;

        light.outerConeAngle =
            gltfLight.spot_outer_cone_angle;

        switch (gltfLight.type)
        {
        case cgltf_light_type_directional:
            light.type = SceneLightType::Directional;
            break;

        case cgltf_light_type_point:
            light.type = SceneLightType::Point;
            break;

        case cgltf_light_type_spot:
            light.type = SceneLightType::Spot;
            break;

        default:
            continue;
        }

        float worldMatrix[16]{};

        cgltf_node_transform_world(
            &node,
            worldMatrix
        );

        light.position = {
            worldMatrix[12],
            worldMatrix[13],
            worldMatrix[14]
        };

        light.direction = Vector3Normalize({
            -worldMatrix[8],
            -worldMatrix[9],
            -worldMatrix[10]
            });

        lights.push_back(light);

        std::cout << "[GLTF] Loaded light: " << light.name
            << " | type: " << static_cast<int>(light.type)
            << " | pos: "
            << light.position.x << ", "
            << light.position.y << ", "
            << light.position.z
            << " | intensity: " << light.intensity
            << " | range: " << light.range
            << '\n';

    }

    cgltf_free(data);
    std::cout << "[GLTF] Total scene lights loaded: "
        << lights.size()
        << '\n';

    return lights;
}