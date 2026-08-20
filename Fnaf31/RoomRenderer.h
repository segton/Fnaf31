#pragma once
#include "RoomScene.h"

class RoomRenderer
{
public:
    void init();

    void draw(const RoomScene& scene) const;

    void drawModel(
        const Model& model,
        const Camera3D& camera,
        Vector3 position,
        float scale,
        const std::vector<SceneLight>& lights) const;

    void applyShader(Model& model);

    void beginCCTVRender() const;
    void endCCTVRender() const;

    void drawCCTVTarget(float time) const;

    void shutdown();

private:
    void uploadCameraUniforms(const Camera3D& camera) const;
    //void uploadLightUniforms(const std::vector<SceneLight>& lights) const;

private:

    RenderTexture2D m_cctvTarget{};
    Shader m_staticShader{};

    int m_timeLoc = -1;
    int m_resolutionLoc = -1;

    Shader m_pbrShader{};

    int m_viewPosLoc = -1;
    int m_numLightsLoc = -1;

    int m_albedoColorLoc = -1;
    int m_metallicValueLoc = -1;
    int m_roughnessValueLoc = -1;
    int m_aoValueLoc = -1;

    int m_ambientColorLoc = -1;
    int m_ambientLoc = -1;

};
