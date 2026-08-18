#pragma once
#include "raylib.h"
#include "OfficeCamera.h"
#include "CCTV.h"
#include "Enemy.h"
#include "DurianEnemy.h"
#include "EnemyContext.h"

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
	void shutdown() const;

private:
	void drawOffice() const;
	void drawCCTV() const;

private:
	GameState m_gameState = GameState::Playing;
	OfficeCamera m_officeCamera{};

	OfficeState m_officeState{};
	NightState m_nightState{};

	CCTV m_cctv{};

	Vector3 m_worldOrigin = { 0.0f, 0.0f, 0.0f };

	Model m_officeModel{};


	//enemy
	EnemyContext enemyContext{ false ,false,false,Room::MainHall};

	DurianEnemy durian{ Room::MainStage, 7, 5.f };
};

