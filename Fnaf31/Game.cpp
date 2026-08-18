#include "Game.h"
#include <iostream>


void Game::init()
{
    m_gameState = GameState::Playing;

    m_officeState = {};
    m_nightState = {};

    m_officeCamera.init();
    m_cctv.init();

    durian = { Room::MainStage, 20, 1.f };

    m_officeModel = LoadModel("Assets/3D/Office2.glb");
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
        durian.update(dt,enemyContext);

        if (!m_cctv.isOpen())
        {
            m_officeCamera.update(dt);
            if (IsKeyPressed(KEY_A))
            {
                m_officeState.leftDoorClosed = !m_officeState.leftDoorClosed;
                std::cout << "Left door is " << (m_officeState.leftDoorClosed ? "closed\n" : "opened\n");
            }

            if (IsKeyPressed(KEY_D))
            {
                m_officeState.rightDoorClosed = !m_officeState.rightDoorClosed;
                std::cout << "Right door is " << (m_officeState.rightDoorClosed ? "closed\n" : "opened\n");
            }

        }
        else
        {
			m_cctv.update(dt);
            m_cctv.handleInput();
        }

        enemyContext.leftDoorClosed = m_officeState.leftDoorClosed;
        enemyContext.rightDoorClosed = m_officeState.rightDoorClosed;
        enemyContext.cctvOpen = m_cctv.isOpen();
        enemyContext.selectedRoom = m_cctv.getSelectedRoom();
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

    DrawModel(m_officeModel, m_worldOrigin, 1.0f, LIGHTGRAY);

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

