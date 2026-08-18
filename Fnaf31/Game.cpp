#include "Game.h"



void Game::init()
{
    m_gameState = GameState::Playing;

    m_officeState = {};
    m_nightState = {};

    m_officeCamera.init();
    m_cctv.init();

    m_officeModel = LoadModel("Assets/3D/Office.glb");
}

void Game::update()
{
	float dt = GetFrameTime();

    if (IsKeyPressed(KEY_SPACE))
    {
        m_cctv.toggle();
    }

    if (m_gameState == GameState::Playing)
    {
        if (!m_cctv.isOpen())
        {
            m_officeCamera.update(dt);
        }
        else
        {
			m_cctv.update(dt);
            m_cctv.handleInput();
        }
    }
}

void Game::draw() const
{
    if (m_gameState == GameState::Playing)
    {
        if (!m_cctv.isOpen())
        {
            drawOffice();
        }
        else
        {
            drawCCTV();
        }
    }
}

void Game::drawOffice() const
{
    BeginMode3D(m_officeCamera.getCamera());

    DrawModel(m_officeModel, m_worldOrigin, 1.0f, WHITE);

    EndMode3D();
}

void Game::drawCCTV() const
{
	m_cctv.draw();
}


void Game::shutdown() const
{
    UnloadModel(m_officeModel);
}

