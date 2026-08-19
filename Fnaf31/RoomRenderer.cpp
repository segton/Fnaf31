#include <iostream>
#include <string>
#include "RoomRenderer.h"

void RoomRenderer::init()
{
    const char* vertexPath = "Assets/shaders/pbr.vs";
    const char* fragmentPath = "Assets/shaders/pbr.fs";

    std::cout << "[PBR] VS exists: "
        << FileExists(vertexPath)
        << '\n';

    std::cout << "[PBR] FS exists: "
        << FileExists(fragmentPath)
        << '\n';

    m_pbrShader = LoadShader(
        vertexPath,
        fragmentPath
    );

    std::cout << "[PBR] Shader ID: "
        << m_pbrShader.id
        << '\n';

    // 2. THEN ask that shader for uniform locations
    m_viewPosLoc =
        GetShaderLocation(m_pbrShader, "viewPos");

    m_numLightsLoc =
        GetShaderLocation(m_pbrShader, "numOfLights");

    m_albedoColorLoc =
        GetShaderLocation(m_pbrShader, "albedoColor");

    m_metallicValueLoc =
        GetShaderLocation(m_pbrShader, "metallicValue");

    m_roughnessValueLoc =
        GetShaderLocation(m_pbrShader, "roughnessValue");

    m_aoValueLoc =
        GetShaderLocation(m_pbrShader, "aoValue");

    m_ambientColorLoc =
        GetShaderLocation(m_pbrShader, "ambientColor");

    m_ambientLoc =
        GetShaderLocation(m_pbrShader, "ambient");

    std::cout << "[PBR] numOfLights loc: "
        << GetShaderLocation(m_pbrShader, "numOfLights")
        << '\n';

    std::cout << "[PBR] viewPos loc: "
        << GetShaderLocation(m_pbrShader, "viewPos")
        << '\n';

    std::cout << "[PBR] albedoColor loc: "
        << GetShaderLocation(m_pbrShader, "albedoColor")
        << '\n';

    std::cout << "[PBR] lights[0].enabled loc: "
        << GetShaderLocation(
            m_pbrShader,
            "lights[0].enabled"
        )
        << '\n';

    const float albedo[4] =
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f
    };

    const float metallic = 0.0f;
    const float roughness = 0.5f;
    const float ao = 1.0f;

    const float ambientColor[3] =
    {
        1.0f,
        1.0f,
        1.0f
    };

    const float ambient = 0.15f;

    SetShaderValue(
        m_pbrShader,
        m_albedoColorLoc,
        albedo,
        SHADER_UNIFORM_VEC4
    );

    SetShaderValue(
        m_pbrShader,
        m_metallicValueLoc,
        &metallic,
        SHADER_UNIFORM_FLOAT
    );

    SetShaderValue(
        m_pbrShader,
        m_roughnessValueLoc,
        &roughness,
        SHADER_UNIFORM_FLOAT
    );

    SetShaderValue(
        m_pbrShader,
        m_aoValueLoc,
        &ao,
        SHADER_UNIFORM_FLOAT
    );

    SetShaderValue(
        m_pbrShader,
        m_ambientColorLoc,
        ambientColor,
        SHADER_UNIFORM_VEC3
    );

    SetShaderValue(
        m_pbrShader,
        m_ambientLoc,
        &ambient,
        SHADER_UNIFORM_FLOAT
    );


}

void RoomRenderer::draw(const RoomScene& scene) const
{
    drawModel(
        scene.model,
        scene.camera,
        scene.modelPosition,
        scene.modelScale,
        scene.lights
    );
}

void RoomRenderer::drawModel(const Model& model, const Camera3D& camera, Vector3 position, float scale, const std::vector<SceneLight>& lights) const
{
    uploadCameraUniforms(camera);
    uploadLightUniforms(lights);

    BeginMode3D(camera);

    DrawModel(
        model,
        position,
        scale,
        WHITE
    );

    EndMode3D();
}

void RoomRenderer::applyShader(Model& model)
{
	for (int i = 0; i < model.materialCount; ++i)
	{
		model.materials[i].shader = m_pbrShader;
	}
}

void RoomRenderer::shutdown()
{
	UnloadShader(m_pbrShader);

}

void RoomRenderer::uploadCameraUniforms(const Camera3D& camera) const
{
    const float position[3]{
        camera.position.x,
        camera.position.y,
        camera.position.z
    };

    SetShaderValue(
        m_pbrShader,
        m_viewPosLoc,
        position,
        SHADER_UNIFORM_VEC3
    );
}

void RoomRenderer::uploadLightUniforms(
    const std::vector<SceneLight>& lights
) const
{
    constexpr int maxLights = 12;

    int lightCount = 0;

    for (const SceneLight& light : lights)
    {
        if (lightCount >= maxLights)
        {
            break;
        }

        // Your shader does not support Spot yet.
        if (light.type == SceneLightType::Spot)
        {
            continue;
        }

        const std::string prefix =
            "lights[" + std::to_string(lightCount) + "].";

        const int enabledLoc =
            GetShaderLocation(
                m_pbrShader,
                (prefix + "enabled").c_str()
            );

        const int typeLoc =
            GetShaderLocation(
                m_pbrShader,
                (prefix + "type").c_str()
            );

        const int positionLoc =
            GetShaderLocation(
                m_pbrShader,
                (prefix + "position").c_str()
            );

        const int targetLoc =
            GetShaderLocation(
                m_pbrShader,
                (prefix + "target").c_str()
            );

        const int colorLoc =
            GetShaderLocation(
                m_pbrShader,
                (prefix + "color").c_str()
            );

        const int intensityLoc =
            GetShaderLocation(
                m_pbrShader,
                (prefix + "intensity").c_str()
            );

        const int rangeLoc =
            GetShaderLocation(
                m_pbrShader,
                (prefix + "range").c_str()
            );

        const int enabled = 1;

        int type = 0;

        if (light.type == SceneLightType::Point)
        {
            type = 1;
        }

        const float position[3] =
        {
            light.position.x,
            light.position.y,
            light.position.z
        };

        const Vector3 targetVector =
        {
            light.position.x + light.direction.x,
            light.position.y + light.direction.y,
            light.position.z + light.direction.z
        };

        const float target[3] =
        {
            targetVector.x,
            targetVector.y,
            targetVector.z
        };

        const float color[4] =
        {
            light.color.x,
            light.color.y,
            light.color.z,
            1.0f
        };

        const float intensity = light.intensity;

        // glTF range == 0 means no explicit range.
        // Temporary large value until shader handles infinite range.
        const float range =
            light.range > 0.0f
            ? light.range
            : 1000.0f;

        SetShaderValue(
            m_pbrShader,
            enabledLoc,
            &enabled,
            SHADER_UNIFORM_INT
        );

        SetShaderValue(
            m_pbrShader,
            typeLoc,
            &type,
            SHADER_UNIFORM_INT
        );

        SetShaderValue(
            m_pbrShader,
            positionLoc,
            position,
            SHADER_UNIFORM_VEC3
        );

        SetShaderValue(
            m_pbrShader,
            targetLoc,
            target,
            SHADER_UNIFORM_VEC3
        );

        SetShaderValue(
            m_pbrShader,
            colorLoc,
            color,
            SHADER_UNIFORM_VEC4
        );

        SetShaderValue(
            m_pbrShader,
            intensityLoc,
            &intensity,
            SHADER_UNIFORM_FLOAT
        );

        SetShaderValue(
            m_pbrShader,
            rangeLoc,
            &range,
            SHADER_UNIFORM_FLOAT
        );

        ++lightCount;
    }

    SetShaderValue(
        m_pbrShader,
        m_numLightsLoc,
        &lightCount,
        SHADER_UNIFORM_INT
    );
}
