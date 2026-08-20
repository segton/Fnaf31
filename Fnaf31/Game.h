#pragma once
#include<memory>
#include "raylib.h"

//main office camera and camera panel logic
#include "OfficeCamera.h"
#include "CCTV.h"

//--enemy classes
#include "Enemy.h"
#include "DurianEnemy.h"
#include "EnemyContext.h"
#include "EnemyVisual.h"

//--rendering rooms
#include "RoomRenderer.h"
#include "RoomScene.h"


//--audio manager
#include "AudioManager.h"


enum class GameState
{
	Menu,
	Playing,
	Win,
	Lose,
}; 

struct OfficeState
{
	bool leftDoorClosed = false;
	bool rightDoorClosed = false;

	float leftDoorProgress = 0.0f;
	float rightDoorProgress = 0.0f;

	bool leftLightOn = false;
	bool rightLightOn = false;
};

struct NightState
{
	int currentHour = 12;
	int currentMinute = 0;
	int currentSecond = 0;
	float elapsedTime = 0.0f;
};

struct PowerState
{
	float battery = 100.0f;

	// percentage points drained per second
	float baseDrain = 0.02f;
	float doorDrain = 0.2f;
	float lightDrain = 0.1f;

	bool isOut() const
	{
		return battery <= 0.0f;
	}
};

class Game
{
public:
	Game() = default;
	void init();
	void update();
	void draw() const;
	void shutdown();


private:
	void drawOffice() const;
	void drawCCTV() const;
	void drawMenu() const;

	void startGame();
	void returnToMenu();

	void initEnemies();
	void initRooms();

	const RoomScene* findRoomScene(const Room& room) const;

	void initEnemyVisuals();

	const EnemyVisual* findEnemyVisual(EnemyType type) const;

	const EnemyBillboardPose* findEnemyPose(const EnemyVisual& visual,Room room) const;

	//game state
	void updatePower(float dt);
	void drawPowerUI() const;
	void updateDoors(float dt);
	void drawDoors() const;

	void drawDoorLight(Vector3 worldPosition) const;

	void drawOfficeEnemiesAtRoom(Room doorRoom,Vector3 position,float scale) const;

	void startJumpscare(EnemyType type);
	void drawJumpscare() const;

private:
	GameState m_gameState = GameState::Playing;
	OfficeCamera m_officeCamera{};

	OfficeState m_officeState{};
	NightState m_nightState{};

	CCTV m_cctv{};

	Vector3 m_worldOrigin = { 0.0f, 0.0f, 0.0f };

	//Office models
	Model m_officeModel{};
	Model m_doorModel{};

	//enemy
	EnemyContext enemyContext{ false ,false,false,Room::MainHall };

	//DurianEnemy durian{ Room::MainStage, 7, 5.f };
	std::vector<EnemyVisual> m_enemyVisuals{};


	std::vector<std::unique_ptr<Enemy>> m_enemies;

	//room rendering
	RoomRenderer m_roomRenderer{};
	std::vector<RoomScene> m_roomScenes{};

	//const Room m_selectedRoom{};

	//audio
	AudioManager m_audio;

	PowerState m_powerState{};

	//death screen
	bool m_jumpscareActive = false;

	EnemyType m_jumpscareEnemy = EnemyType::Durian;

	float m_jumpscareTimer = 0.0f;



};

