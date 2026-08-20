#include "Game.h"

#include <iostream>
#include "GltfSceneLoader.h"
#include "MangosteenEnemy.h"
#include "JambuEnemy.h"
#include "RambutanEnemy.h"
#include "RoomRenderer.h"

namespace
{
    // Enemy reveal positions
    const Vector3 lWinEnemyPos = { -6.6302f, 5.213f, 5.4283f };
    const Vector3 lDoorEnemyPos = { -7.7866f, 5.213f, 10.019f };

    const Vector3 rWinEnemyPos = { 6.6302f, 5.213f, 5.4283f };
    const Vector3 rDoorEnemyPos = { 7.7866f, 5.213f, 10.019f };

    // fake light positions
    const Vector3 lLightPos = lDoorEnemyPos;
    const Vector3 rLightPos = rDoorEnemyPos;

    // door positions
    const Vector3 lDoorClosed = { -7.56f, 3.92f, 10.13f };
    const Vector3 lDoorOpen = { -7.56f, 12.92f, 10.13f };

    const Vector3 rDoorClosed = { 7.56f, 3.92f, 10.13f };
    const Vector3 rDoorOpen = { 7.56f, 12.92f, 10.13f };

    // door rotations in degrees
    constexpr float lDoorRot = -8.1f;
    constexpr float rDoorRot = 8.1f;
}

void Game::init()
{
    m_gameState = GameState::Menu;

    m_officeState = {};
    m_nightState = {};

    m_officeCamera.init();
    m_cctv.init(*this, m_audio);

    //create enemies
    initEnemies();

    initEnemyVisuals();

    //create other rooms
    m_roomRenderer.init();
    initRooms();
    m_officeModel = LoadModel("Assets/3D/Office4.glb");

    m_doorModel = LoadModel("Assets/3D/door.glb");

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

    m_audio.loadSound("retreat", "Assets/Audio/enemy_retreat.mp3");

    m_audio.loadSound("light", "Assets/Audio/light_sound.mp3");

    m_audio.loadSound("change_cam", "Assets/Audio/change_cam.mp3");

    m_audio.loadSound("jumpscare", "Assets/Audio/jumpscare.mp3");

    m_audio.loadMusic("ambience", "Assets/Audio/ambience.ogg");


    m_audio.playMusic("ambience");
}

void Game::initEnemies()
{
    m_enemies.clear();

    m_enemies.emplace_back(std::make_unique<DurianEnemy>(Room::MainStage,6,5.0f,m_audio));

    m_enemies.emplace_back(std::make_unique<MangosteenEnemy>(Room::MainStage,5,4.0f, m_audio));

    m_enemies.emplace_back(std::make_unique<JambuEnemy>(Room::MainStage,8,4.0f, m_audio));

    m_enemies.emplace_back(std::make_unique<RambutanEnemy>(Room::GameStalls,6,5.0f, m_audio));
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

void Game::startGame()
{
    m_gameState =
        GameState::Playing;

    m_jumpscareActive = false;
    m_jumpscareTimer = 0.0f;

    m_officeState = {};
    m_nightState = {};
    m_powerState = {};

    initEnemies();

    m_audio.playMusic(
        "ambience"
    );
}

void Game::returnToMenu()
{
    m_jumpscareActive = false;
    m_jumpscareTimer = 0.0f;

    m_audio.stopLoopingSound("light");
    m_audio.stopMusic("ambience");

    m_gameState = GameState::Menu;
}

void Game::update()
{
    const float dt = GetFrameTime();

    m_audio.update();

    // ---------------- MENU ----------------

    if (m_gameState == GameState::Menu)
    {
        const Rectangle playButton =
        {
            GetScreenWidth() / 2.0f - 100.0f,
            320.0f,
            200.0f,
            60.0f
        };

        if (
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(
                GetMousePosition(),
                playButton
            )
            )
        {
            startGame();
        }

        return;
    }

    // ---------------- LOSE / JUMPSCARE ----------------

    if (m_gameState == GameState::Lose)
    {
        if (m_jumpscareActive)
        {
            m_jumpscareTimer += dt;

            if (m_jumpscareTimer > 0.1f &&!m_audio.isSoundPlaying("jumpscare"))
            {
                returnToMenu();
            }
        }

        return;
    }

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

        for (const auto& enemy : m_enemies)
        {
            if (!enemy->hasAttacked())
            {
                continue;
            }

            startJumpscare(enemy->getType());

            break;
        }

        updateDoors(dt);

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
    switch (m_gameState)
    {
    case GameState::Menu:
        drawMenu();
        break;

    case GameState::Playing:

        if (m_cctv.isOpen())
        {
            drawCCTV();
        }
        else
        {
            drawOffice();
        }

        break;

    case GameState::Lose:

        drawOffice();

        if (m_jumpscareActive)
        {
            drawJumpscare();
        }

        break;

    case GameState::Win:
        break;
    }
}

void Game::drawOffice() const
{
    const Camera3D& camera =
        m_officeCamera.getCamera();

    BeginMode3D(camera);

    DrawModel(
        m_officeModel,
        m_worldOrigin,
        1.0f,
        LIGHTGRAY
    );

    if (m_officeState.leftLightOn)
    {
        drawOfficeEnemiesAtRoom(Room::LeftHall,lWinEnemyPos,2.2f);

        drawOfficeEnemiesAtRoom(Room::LeftDoor,lDoorEnemyPos,2.7f);
    }

    if (m_officeState.rightLightOn)
    {
        drawOfficeEnemiesAtRoom(Room::RightHall,rWinEnemyPos,2.2f);

        drawOfficeEnemiesAtRoom(Room::RightDoor,rDoorEnemyPos,2.7f);
    }

    // Draw after enemies so door can visually cover them.
    drawDoors();

    EndMode3D();

    if (m_officeState.leftLightOn)
    {
        drawDoorLight(lLightPos);
    }

    if (m_officeState.rightLightOn)
    {
        drawDoorLight(rLightPos);
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
        m_roomRenderer.beginCCTVRender();

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

        m_roomRenderer.endCCTVRender();
        m_roomRenderer.drawCCTVTarget(GetTime());
        m_cctv.draw(m_enemies);
    }

    m_cctv.draw(m_enemies);

}

void Game::drawMenu() const
{
    const char* title = "PASAR TENGAH MALAM";

    const int titleSize = 48;

    const int titleWidth =
        MeasureText(title, titleSize);

    DrawText(
        title,
        GetScreenWidth() / 2 - titleWidth / 2,
        160,
        titleSize,
        WHITE
    );

    const Rectangle playButton =
    {
        GetScreenWidth() / 2.0f - 100.0f,
        320.0f,
        200.0f,
        60.0f
    };

    DrawRectangleRec(playButton,DARKGRAY);

    DrawRectangleLinesEx(playButton,2.0f,WHITE);

    const char* text = "PLAY";

    const int textSize = 30;
    const int textWidth =MeasureText(text, textSize);

    DrawText(text,static_cast<int>(playButton.x +
            playButton.width / 2 -
            textWidth / 2
            ),
        static_cast<int>(
            playButton.y +
            playButton.height / 2 -
            textSize / 2
            ),
        textSize,
        WHITE
    );
}

void Game::drawPowerUI() const
{
    DrawText(TextFormat("POWER: %.0f%%",m_powerState.battery),20,
             GetScreenHeight() - 45,
             28,
             WHITE
            );
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

    if (m_officeState.leftLightOn || m_officeState.rightLightOn)
    {
        m_audio.playLoopingSound("light");
    }
    else
    {
        m_audio.stopLoopingSound("light");
    }

    m_powerState.battery -= drain * dt;

    if (m_powerState.battery <= 0.0f)
    {
        m_powerState.battery = 0.0f;

        m_officeState.leftDoorClosed = false;
        m_officeState.rightDoorClosed = false;

        m_officeState.leftLightOn = false;
        m_officeState.rightLightOn = false;

        m_audio.stopLoopingSound("light");
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

void Game::updateDoors(float dt)
{
    const float doorSpeed = 2.0f;

    if (m_officeState.leftDoorClosed)
    {
        m_officeState.leftDoorProgress += doorSpeed * dt;
    }
    else
    {
        m_officeState.leftDoorProgress -= doorSpeed * dt;
    }

    if (m_officeState.rightDoorClosed)
    {
        m_officeState.rightDoorProgress += doorSpeed * dt;
    }
    else
    {
        m_officeState.rightDoorProgress -= doorSpeed * dt;
    }

    m_officeState.leftDoorProgress = Clamp(m_officeState.leftDoorProgress,0.0f,1.0f);

    m_officeState.rightDoorProgress =Clamp(m_officeState.rightDoorProgress,0.0f,1.0f);
}

void Game::drawDoors() const
{
    const Vector3 lDoorPos = Vector3Lerp(lDoorOpen, lDoorClosed, m_officeState.leftDoorProgress);

    const Vector3 rDoorPos = Vector3Lerp(rDoorOpen, rDoorClosed, m_officeState.rightDoorProgress);

    DrawModelEx(m_doorModel,lDoorPos, { 0.0f, 1.0f, 0.0f },lDoorRot,{ 1.0f, 1.0f, 1.0f },WHITE);

    DrawModelEx(m_doorModel, rDoorPos, { 0.0f, 1.0f, 0.0f }, rDoorRot, { 1.0f, 1.0f, 1.0f }, WHITE);
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
            2.0f });

        visual.poses.push_back({
            Room::FoodCourt,
            { 0.0f, 1.5f, 0.0f },
            2.0f });

        visual.poses.push_back({
            Room::MainHall,
            { 0.0f, 1.5f, 0.0f },
            2.0f });

        visual.poses.push_back({
            Room::RightHall,
            { 0.0f, 1.5f, 0.0f },
            2.0f });

        visual.poses.push_back({
            Room::RightDoor,
            { 0.0f, 1.5f, 0.0f },
            2.0f });

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
            2.0f });

        visual.poses.push_back({
            Room::GameStalls,
            { 0.0f, 1.5f, 0.0f },
            2.0f });

        visual.poses.push_back({
            Room::MainHall,
            { -1.0f, 1.5f, 0.0f },
            2.0f });

        visual.poses.push_back({
            Room::LeftHall,
            { 0.0f, 1.5f, 0.0f },
            2.0f });

        visual.poses.push_back({
            Room::LeftDoor,
            { 0.0f, 1.5f, 0.0f },
            2.0f });

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
            2.0f });

        visual.poses.push_back({
            Room::FoodCourt,
            { 0.0f, 1.5f, 0.0f },
            2.0f });

        visual.poses.push_back({
            Room::MainHall,
            { 1.0f, 1.5f, 0.0f },
            2.0f });

        visual.poses.push_back({
            Room::RightHall,
            { 0.0f, 1.5f, 0.0f },
            2.0f });

        visual.poses.push_back({
            Room::RightDoor,
            { 0.0f, 1.5f, 0.0f },
            2.0f });

        m_enemyVisuals.push_back(
            std::move(visual)
        );
    }

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
            2.0f });

        visual.poses.push_back({
            Room::LeftHall,
            { 0.0f, 1.5f, 0.0f },
            2.2f });

        visual.poses.push_back({
            Room::LeftDoor,
            { 0.0f, 1.5f, 0.0f },
            2.7f });

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

void Game::shutdown()
{

    UnloadModel(m_officeModel);
    UnloadModel(m_doorModel);

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





void Game::drawDoorLight(Vector3 worldPosition) const
{
    const Camera3D& camera = m_officeCamera.getCamera();

    Vector2 screenPosition = GetWorldToScreen(worldPosition,camera);

    //DrawCircleV(screenPosition,10.0f,RED);

    BeginBlendMode(BLEND_ADDITIVE);

    DrawCircleGradient(
        screenPosition,
        320.0f,
        Color{ 120, 190, 255, 200 },
        Color{ 40, 100, 255, 0 });

    EndBlendMode();
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
        static_cast<int>(screenPosition.x),
        static_cast<int>(screenPosition.y),
        260.0f,
        Color{ 255, 235, 170, 110 },
        Color{ 255, 220, 120, 0 }
    );

    EndBlendMode();
}
*/


void Game::drawOfficeEnemiesAtRoom(Room doorRoom,Vector3 position,float scale) const
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

        const EnemyVisual* visual = findEnemyVisual(enemy->getType());

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

void Game::startJumpscare(EnemyType type)
{
    if (m_jumpscareActive)
    {
        return;
    }

    m_jumpscareActive = true;
    m_jumpscareEnemy = type;
    m_jumpscareTimer = 0.0f;

    // Force CCTV monitor down.
    if (m_cctv.isOpen())
    {
        m_cctv.toggle();
    }

    m_audio.stopMusic("ambience");
    m_audio.stopLoopingSound("light");

    m_audio.playSound("jumpscare");

    m_gameState = GameState::Lose;
}

void Game::drawJumpscare() const
{
    const EnemyVisual* visual =findEnemyVisual(m_jumpscareEnemy);

    if (visual == nullptr)
    {
        return;
    }

    const Camera3D& camera = m_officeCamera.getCamera();

    const Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target,camera.position));

    const Vector3 position = Vector3Add(camera.position,Vector3Scale(forward,1.0f));

    BeginMode3D(camera);

    DrawBillboard(camera, visual->texture,position,1.6f,WHITE);

    EndMode3D();
}