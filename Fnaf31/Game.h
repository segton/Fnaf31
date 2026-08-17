#pragma once
#include "raylib.h"
#include "OfficeCamera.h"

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

struct CameraState
{
	bool isCameraPanelOpen = false;
	bool isCameraActive = false;
};

struct NightState
{
	int currentHour = 12;
	int currentMinute = 0;
	int currentSecond = 0;
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
	OfficeCamera camera;

	OfficeState m_officeState;
	CameraState m_cameraState;
	NightState m_nightState;

	Vector3 m_worldOrigin = { 0.0f, 0.0f, 0.0f };

	Model m_officeModel;
};

