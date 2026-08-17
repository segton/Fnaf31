#pragma once

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
	void init();
	void update();
	void draw();
	void shutdown();

};

