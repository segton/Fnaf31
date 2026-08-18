#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Button.h"
#include "Room.h"
#include "DurianEnemy.h"
#include "EnemyInfo.h"

class Game;

struct CCTVButton
{
    Button button;
    Room room;

    Color bgColor = DARKGRAY; //default background color
    Color hoverColor = GRAY; //default hover color

    CCTVButton(
        const Rectangle bounds, const std::string& text, Room cameraRoom) : button(
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

    void init(Game& game);
	void update(float dt);
	void draw(const std::vector<EnemyInfo>& enemies) const;
    bool isOpen() const;
    void toggle();
    void handleInput();

    Room getSelectedRoom() const;

private:
    void drawSelectedRooms() const;

    void drawEnemy(const EnemyInfo& enemyInfo) const;

    void selectRoom(const Room& room);
    void refreshButtons();
private:
    Room  m_selectedRoom = Room::MainStage;
    //DurianEnemy* m_durianPtr = nullptr;

	bool m_isOpen = false;
	std::vector<CCTVButton> m_cameraButtons{};


};