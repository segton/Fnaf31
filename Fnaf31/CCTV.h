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

    Color bgColor = DARKGRAY; //default background color
    Color hoverColor = GRAY; //default hover color

    CCTVButton(
        const Rectangle bounds,
        const std::string& text,
        CCTVRoom cameraRoom) : button(
            bounds,
            text,
            18,
            bgColor,
            hoverColor,
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
    void handleInput();

    CCTVRoom getSelectedRoom() const;

private:
    void drawSelectedRooms() const;

    void selectRoom(const CCTVRoom& room);
    void refreshButtons();
private:
    CCTVRoom m_selectedRoom = CCTVRoom::MainStage;

	bool m_isOpen = false;
	std::vector<CCTVButton> m_cameraButtons{};


};