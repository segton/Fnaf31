#include "Game.h"



void Game::init()
{
	camera.init();
    m_officeModel = LoadModel("Assets/3D/Office.glb");
}

void Game::update()
{
	float dt = GetFrameTime();

    camera.update(dt);

}

void Game::draw() const
{
    BeginMode3D(camera.getCamera());

    DrawModel(m_officeModel, m_worldOrigin, 1.0f, WHITE);

    EndMode3D();
}

void Game::shutdown() const
{
    UnloadModel(m_officeModel);
}
