#pragma once
#include <vector>
#include "Button.h"

enum class CCTVRoom
{
    MainStage,
    FoodCourt,
    GameStalls,
    MainHall,
    LeftHall,
    RightHall
};

struct CCTVButton
{
    Button button;
    CCTVRoom room;

    CCTVButton(
        const Rectangle bounds,
        const std::string& text,
        CCTVRoom cameraRoom) : button(
            bounds,
            text,
            18,
            DARKGRAY,
            GRAY,
            WHITE,
            LIGHTGRAY
        ),
        room(cameraRoom)
    {
    }
};

class CCTV
{
public:

    void init();
	void update(float dt);
	void draw() const;
    bool isOpen() const;
    void toggle();

private:
    CCTVRoom m_selectedRoom = CCTVRoom::MainStage;

	bool m_isOpen = false;
	std::vector<CCTVButton> m_cameraButtons{};


};