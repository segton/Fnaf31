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
	void initEnemies();

	const RoomScene* findRoomScene(const Room& room) const;

private:
	GameState m_gameState = GameState::Playing;
	OfficeCamera m_officeCamera{};

	OfficeState m_officeState{};
	NightState m_nightState{};

	CCTV m_cctv{};

	Vector3 m_worldOrigin = { 0.0f, 0.0f, 0.0f };

	Model m_officeModel{};


	//enemy
	EnemyContext enemyContext{ false ,false,false,Room::MainHall };

	//DurianEnemy durian{ Room::MainStage, 7, 5.f };

	std::vector<std::unique_ptr<Enemy>> m_enemies;

	//room rendering
	RoomRenderer m_roomRenderer{};
	std::vector<RoomScene> m_roomScenes{};

	//const Room m_selectedRoom{};

	//audio
	AudioManager m_audio;

};

