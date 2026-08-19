#include "Game.h"

#include <iostream>
#include "GltfSceneLoader.h"


void Game::init()
{
    m_gameState = GameState::Playing;

    m_officeState = {};
    m_nightState = {};

    m_officeCamera.init();
    m_cctv.init(*this);

    //create enemies
    initEnemies();

    //create other rooms
    m_roomRenderer.init();

    m_officeModel = LoadModel("Assets/3D/Office3.glb");
    //m_roomRenderer.applyShader(m_officeModel);

    //const auto lights = GltfSceneLoader::loadLights("Assets/3D/Office3.glb");

    RoomScene mainStage{};

    mainStage.room = Room::MainStage;
    mainStage.model = LoadModel("Assets/3D/MainStage.glb");

    /*
    mainStage.lights =
        GltfSceneLoader::loadLights(
            "Assets/3D/MainStage.glb"
        );
    */

    mainStage.camera.position = { 0.0f, 3.0f, 8.0f };
    mainStage.camera.target = { 0.0f, 2.0f, 0.0f };
    mainStage.camera.up = { 0.0f, 1.0f, 0.0f };
    mainStage.camera.fovy = 45.0f;
    mainStage.camera.projection = CAMERA_PERSPECTIVE;

    mainStage.modelPosition = { 0.0f, 0.0f, 0.0f };
    mainStage.modelScale = 1.0f;

    //m_roomRenderer.applyShader(mainStage.model); 

    m_roomScenes.push_back(mainStage);


    //load audio

    m_audio.init();

    m_audio.loadSound("door_close", "Assets/Audio/door_close");

}

void Game::initEnemies()
{
    m_enemies.clear();

    m_enemies.emplace_back(
        std::make_unique<DurianEnemy>(
            Room::MainStage,
            20,
            1.0f
        )
    );
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
        enemyContext.leftDoorClosed = m_officeState.leftDoorClosed;
        enemyContext.rightDoorClosed = m_officeState.rightDoorClosed;
        enemyContext.cctvOpen = m_cctv.isOpen();
        enemyContext.selectedRoom = m_cctv.getSelectedRoom();

        for (auto& enemy : m_enemies)
        {
            enemy->update(dt, enemyContext);
        }

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

    const Room selectedRoom = m_cctv.getSelectedRoom();

    const RoomScene* scene = findRoomScene(selectedRoom);

    if (scene == nullptr)
    {
        DrawText("NO 3D SCENE FOR THIS ROOM", 50, 120, 30, RED);
    }
    else
    {
        m_roomRenderer.draw(*scene);
    }

    m_cctv.draw(m_enemies);

}

void Game::shutdown()
{
    UnloadModel(m_officeModel);

    for (RoomScene& scene : m_roomScenes)
    {
        UnloadModel(scene.model);
    }

    m_roomRenderer.shutdown();

    m_roomScenes.clear();
}


const RoomScene* Game::findRoomScene(const Room& room) const
{
    for (const RoomScene& scene : m_roomScenes)
    {
        if (scene.room == room)
        {
            return &scene;
        }
    }

    return nullptr;
}
