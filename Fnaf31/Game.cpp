#include "Game.h"

#include <iostream>
#include "GltfSceneLoader.h"
#include "MangosteenEnemy.h"
#include "JambuEnemy.h"
#include "RambutanEnemy.h"

void Game::init()
{
    m_gameState = GameState::Playing;

    m_officeState = {};
    m_nightState = {};

    m_officeCamera.init();
    m_cctv.init(*this);

    //create enemies
    initEnemies();

    initEnemyVisuals();

    //create other rooms
    m_roomRenderer.init();
    initRooms();
    m_officeModel = LoadModel("Assets/3D/Office3.glb");
    //m_roomRenderer.applyShader(m_officeModel);

    //const auto lights = GltfSceneLoader::loadLights("Assets/3D/Office3.glb");
    /*
    RoomScene mainStage{};

    mainStage.room = Room::MainStage;
    mainStage.model = LoadModel("Assets/3D/MainStage.glb");

    /*
    mainStage.lights =
        GltfSceneLoader::loadLights(
            "Assets/3D/MainStage.glb"
        );
    

    mainStage.camera.position = { 0.0f, 3.0f, 8.0f };
    mainStage.camera.target = { 0.0f, 2.0f, 0.0f };
    mainStage.camera.up = { 0.0f, 1.0f, 0.0f };
    mainStage.camera.fovy = 45.0f;
    mainStage.camera.projection = CAMERA_PERSPECTIVE;

    mainStage.modelPosition = { 0.0f, 0.0f, 0.0f };
    mainStage.modelScale = 1.0f;

    //m_roomRenderer.applyShader(mainStage.model); 

    m_roomScenes.push_back(mainStage);
    */

    //load audio

    m_audio.init();

    m_audio.loadSound("door_close", "Assets/Audio/door_close.mp3");

    m_audio.loadSound("door_open", "Assets/Audio/door_close.mp3");

    m_audio.loadSound("cctv_open", "Assets/Audio/camera_open.mp3");

    m_audio.loadMusic("ambience", "Assets/Audio/ambience.ogg");

    m_audio.playMusic("ambience");
}

void Game::initEnemies()
{
    m_enemies.clear();

    m_enemies.emplace_back(std::make_unique<DurianEnemy>(Room::MainStage,4,5.0f));

    m_enemies.emplace_back(std::make_unique<MangosteenEnemy>(Room::MainStage,5,4.0f));

    m_enemies.emplace_back(std::make_unique<JambuEnemy>(Room::MainStage,5,4.0f));

    m_enemies.emplace_back(std::make_unique<RambutanEnemy>(Room::GameStalls,4,5.0f));
}

void Game::initRooms()
{
    m_roomScenes.clear();
    m_roomScenes.reserve(8);

    auto addRoom =[this](
        Room room,
        const char* modelPath,
        Vector3 cameraPosition,
        Vector3 cameraTarget)
    {
        m_roomScenes.emplace_back();

        RoomScene& scene =
            m_roomScenes.back();

        scene.room = room;

        scene.model =
            LoadModel(modelPath);

        scene.camera.position =
            cameraPosition;

        scene.camera.target =
            cameraTarget;

        scene.camera.up =
        {
            0.0f,
            1.0f,
            0.0f
        };

        scene.camera.fovy = 45.0f;

        scene.camera.projection =
            CAMERA_PERSPECTIVE;

        scene.modelPosition =
        {
            0.0f,
            0.0f,
            0.0f
        };

        scene.modelScale = 1.0f;
    };

    addRoom(
        Room::MainStage,
        "Assets/3D/MainStage.glb",
        { 0.0f, 3.0f, 8.0f },
        { 0.0f, 2.0f, 0.0f });

    addRoom(
        Room::FoodCourt,
        "Assets/3D/FoodCourt.glb",
        { 0.0f, 3.0f, 8.0f },
        { 0.0f, 2.0f, 0.0f });

    addRoom(
        Room::GameStalls,
        "Assets/3D/GameStalls.glb",
        { 0.0f, 3.0f, 8.0f },
        { 0.0f, 2.0f, 0.0f });

    addRoom(
        Room::MainHall,
        "Assets/3D/MainHall.glb",
        { 0.0f, 3.0f, 8.0f },
        { 0.0f, 2.0f, 0.0f });

    addRoom(
        Room::LeftHall,
        "Assets/3D/LeftHall.glb",
        { 0.0f, 3.0f, 8.0f },
        { 0.0f, 2.0f, 0.0f });

    addRoom(
        Room::RightHall,
        "Assets/3D/RightHall.glb",
        { 0.0f, 3.0f, 8.0f },
        { 0.0f, 2.0f, 0.0f });

    addRoom(
        Room::LeftDoor,
        "Assets/3D/LeftDoor.glb",
        { 0.0f, 3.0f, 8.0f },
        { 0.0f, 2.0f, 0.0f });

    addRoom(
        Room::RightDoor,
        "Assets/3D/RightDoor.glb",
        { 0.0f, 3.0f, 8.0f },
        { 0.0f, 2.0f, 0.0f });

}


void Game::update()
{
	float dt = GetFrameTime();

    m_audio.update();

    if (IsKeyPressed(KEY_SPACE))
    {
        m_cctv.toggle();
        m_audio.playSound("cctv_open");
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
                if (m_officeState.leftDoorClosed)
                {
                    m_audio.playSound("door_close");
                }
                else
                {
                    m_audio.playSound("door_open");
                }

            }

            if (IsKeyPressed(KEY_D))
            {
                m_officeState.rightDoorClosed = !m_officeState.rightDoorClosed;
                std::cout << "Right door is " << (m_officeState.rightDoorClosed ? "closed\n" : "opened\n");
                if (m_officeState.rightDoorClosed)
                {
                    m_audio.playSound("door_close");
                }
                else
                {
                    m_audio.playSound("door_open");
                }
            }

            m_officeState.leftLightOn = IsKeyDown(KEY_Q);

            m_officeState.rightLightOn = IsKeyDown(KEY_E);

        }
        else
        {
			m_cctv.update(dt);
            m_cctv.handleInput();
        }

        //power
        updatePower(dt);

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
    const Camera3D& camera =
        m_officeCamera.getCamera();

    const Vector3 LEFT_ENEMY_POSITION =
    {
        -8.0f,
        3.0f,
        14.0f
    };

    const Vector3 RIGHT_ENEMY_POSITION =
    {
        8.0f,
        3.0f,
        14.0f
    };

    const Vector3 LEFT_LIGHT_POSITION =
    {
        -8.0f,
        4.0f,
        14.0f
    };

    const Vector3 RIGHT_LIGHT_POSITION =
    {
        8.0f,
        4.0f,
        14.0f
    };

    BeginMode3D(camera);

    DrawModel(
        m_officeModel,
        m_worldOrigin,
        1.0f,
        LIGHTGRAY
    );

    // Enemies are ONLY visible if
    // their respective door light is on.

    if (m_officeState.leftLightOn)
    {
        drawOfficeDoorEnemies(
            Room::LeftDoor,
            LEFT_ENEMY_POSITION,
            2.5f
        );
    }

    if (m_officeState.rightLightOn)
    {
        drawOfficeDoorEnemies(
            Room::RightDoor,
            RIGHT_ENEMY_POSITION,
            2.5f
        );
    }

    EndMode3D();

    // Fake 2D light overlays

    if (m_officeState.leftLightOn)
    {
        drawDoorLight(
            LEFT_LIGHT_POSITION
        );
    }

    if (m_officeState.rightLightOn)
    {
        drawDoorLight(
            RIGHT_LIGHT_POSITION
        );
    }

    drawPowerUI();
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

        for (const auto& enemy : m_enemies)
        {
            if (!enemy->isActive())
            {
                continue;
            }

            if (enemy->getCurrentRoom() != selectedRoom)
            {
                continue;
            }

            const EnemyVisual* visual = findEnemyVisual(enemy->getType());

            if (visual == nullptr)
            {
                continue;
            }

            const EnemyBillboardPose* pose = findEnemyPose(*visual,selectedRoom);

            if (pose == nullptr)
            {
                continue;
            }

            BeginMode3D(scene->camera);

            DrawBillboard(
                scene->camera,
                visual->texture,
                pose->position,
                pose->scale,
                WHITE);

            EndMode3D();
        }

    }

    m_cctv.draw(m_enemies);

}

void Game::drawPowerUI() const
{
    DrawText(
        TextFormat(
            "POWER: %.0f%%",
            m_powerState.battery
        ),
        20,
        GetScreenHeight() - 45,
        28,
        WHITE
    );
}

void Game::shutdown()
{

    UnloadModel(m_officeModel);

    for (RoomScene& scene : m_roomScenes)
    {
        UnloadModel(scene.model);
    }

    m_roomScenes.clear();

    m_roomRenderer.shutdown();

    for (EnemyVisual& visual : m_enemyVisuals)
    {
        UnloadTexture(
            visual.texture
        );
    }

    m_enemyVisuals.clear();

    m_audio.shutdown();
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

void Game::initEnemyVisuals()
{
    m_enemyVisuals.clear();
    m_enemyVisuals.reserve(4);

    // -- DURIAN --

    {
        EnemyVisual visual{};

        visual.type =
            EnemyType::Durian;

        visual.texture =
            LoadTexture("Assets/Images/durian.png");

        visual.poses.push_back({
            Room::MainStage,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::FoodCourt,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::MainHall,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::RightHall,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::RightDoor,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        m_enemyVisuals.push_back(
            std::move(visual));
    }

    // -- MANGOSTEEN --

    {
        EnemyVisual visual{};

        visual.type =
            EnemyType::Mangosteen;

        visual.texture =
            LoadTexture("Assets/Images/mangosteen.png");

        visual.poses.push_back({
            Room::MainStage,
            { -1.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::GameStalls,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::MainHall,
            { -1.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::LeftHall,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::LeftDoor,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        m_enemyVisuals.push_back(
            std::move(visual));
    }

    // -- JAMBU --

    {
        EnemyVisual visual{};

        visual.type =
            EnemyType::Jambu;

        visual.texture =
            LoadTexture("Assets/Images/jambu.png");

        visual.poses.push_back({
            Room::MainStage,
            { 1.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::FoodCourt,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::MainHall,
            { 1.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::RightHall,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::RightDoor,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        m_enemyVisuals.push_back(
            std::move(visual)
        );}

    // -- RAMBUTAN --

    {
        EnemyVisual visual{};

        visual.type =
            EnemyType::Rambutan;

        visual.texture =
            LoadTexture(
                "Assets/Images/rambutan.png"
            );

        visual.poses.push_back({
            Room::GameStalls,
            { 0.0f, 1.5f, 0.0f },
            2.0f});

        visual.poses.push_back({
            Room::LeftHall,
            { 0.0f, 1.5f, 0.0f },
            2.2f});

        visual.poses.push_back({
            Room::LeftDoor,
            { 0.0f, 1.5f, 0.0f },
            2.7f});

        m_enemyVisuals.push_back(
            std::move(visual));
    }
}

const EnemyVisual* Game::findEnemyVisual(EnemyType type) const
{
    for (const EnemyVisual& visual : m_enemyVisuals)
    {
        if (visual.type == type)
        {
            return &visual;
        }
    }

    return nullptr;
}
const EnemyBillboardPose* Game::findEnemyPose(const EnemyVisual& visual, Room room) const
{
    for (const EnemyBillboardPose& pose : visual.poses)
    {
        if (pose.room == room)
        {
            return &pose;
        }
    }

    return nullptr;
}

void Game::updatePower(float dt)
{
    if (m_powerState.isOut())
    {
        return;
    }

    float drain = m_powerState.baseDrain;

    if (m_cctv.isOpen())
    {
        drain += m_powerState.baseDrain;
    }

    if (m_officeState.leftDoorClosed)
    {
        drain += m_powerState.doorDrain;
    }

    if (m_officeState.rightDoorClosed)
    {
        drain += m_powerState.doorDrain;
    }

    if (m_officeState.leftLightOn)
    {
        drain += m_powerState.lightDrain;
    }

    if (m_officeState.rightLightOn)
    {
        drain += m_powerState.lightDrain;
    }

    m_powerState.battery -= drain * dt;

    if (m_powerState.battery <= 0.0f)
    {
        m_powerState.battery = 0.0f;

        // FNAF-style power failure
        m_officeState.leftDoorClosed = false;
        m_officeState.rightDoorClosed = false;

        m_officeState.leftLightOn = false;
        m_officeState.rightLightOn = false;
    }
}
/*
void Game::drawDoorLight(Vector3 worldPosition) const
{
    const Camera3D& camera =
        m_officeCamera.getCamera();

    Vector2 screenPosition =
        GetWorldToScreen(
            worldPosition,
            camera
        );

    BeginBlendMode(BLEND_ADDITIVE);

    DrawCircleGradient(
        screenPosition,
        260.0f,
        Color{ 255, 235, 170, 110 },
        Color{ 255, 220, 120, 0 }
    );

    EndBlendMode();
}
*/

void Game::drawDoorLight(Vector3 worldPosition) const
{
    const Camera3D& camera =
        m_officeCamera.getCamera();

    Vector2 screenPosition =
        GetWorldToScreen(
            worldPosition,
            camera
        );

    BeginBlendMode(BLEND_ADDITIVE);

    DrawCircleGradient(
        static_cast<int>(screenPosition.x),
        static_cast<int>(screenPosition.y),
        260.0f,
        Color{ 255, 235, 170, 110 },
        Color{ 255, 220, 120, 0 }
    );

    EndBlendMode();
}

void Game::drawOfficeDoorEnemies(
    Room doorRoom,
    Vector3 position,
    float scale
) const
{
    const Camera3D& camera =
        m_officeCamera.getCamera();

    for (const auto& enemy : m_enemies)
    {
        if (!enemy->isActive())
        {
            continue;
        }

        if (enemy->getCurrentRoom() != doorRoom)
        {
            continue;
        }

        const EnemyVisual* visual =
            findEnemyVisual(
                enemy->getType()
            );

        if (visual == nullptr)
        {
            continue;
        }

        DrawBillboard(
            camera,
            visual->texture,
            position,
            scale,
            WHITE
        );
    }
}
