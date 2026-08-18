#include "CCTV.h"
#include <iostream>

void CCTV::init()
{
    m_cameraButtons.clear();
    m_cameraButtons.reserve(6);

    m_cameraButtons.emplace_back(
        Rectangle{ 625.0f, 360.0f, 70.0f, 32.0f },
        "CAM 01",
        CCTVRoom::MainStage);

    m_cameraButtons.emplace_back(
        Rectangle{ 545.0f, 405.0f, 70.0f, 32.0f },
        "CAM 02",
        CCTVRoom::FoodCourt);

    m_cameraButtons.emplace_back(
        Rectangle{ 705.0f, 405.0f, 70.0f, 32.0f },
        "CAM 03",
        CCTVRoom::GameStalls);

    m_cameraButtons.emplace_back(
        Rectangle{ 625.0f, 405.0f, 70.0f, 32.0f },
        "CAM 04",
        CCTVRoom::MainHall);

    m_cameraButtons.emplace_back(
        Rectangle{ 585.0f, 450.0f, 70.0f, 32.0f },
        "CAM 05",
        CCTVRoom::LeftHall);

    m_cameraButtons.emplace_back(
        Rectangle{ 665.0f, 450.0f, 70.0f, 32.0f },
        "CAM 06",
        CCTVRoom::RightHall);

    refreshButtons();
}

void CCTV::update(float dt)
{
    /*
        for (CCTVButton& camera : m_cameraButtons)
    {
        if (camera.room == m_selectedRoom) //active room
        {
            camera.button.setBackgroundColor(BLUE);
            camera.button.setHoverColor({ 173, 216, 230, 255 });
            continue;
        }

        if (camera.button.isClicked())
        {
            m_selectedRoom = camera.room;
        }
        else
        {
            camera.button.setBackgroundColor(camera.bgColor);
            camera.button.setHoverColor(camera.hoverColor);
        }
    }
    */

}

void CCTV::draw() const
{
    drawSelectedRooms();

	for (const CCTVButton& b : m_cameraButtons)
	{
		b.button.draw();
	}
}

void CCTV::toggle()
{
	m_isOpen = !m_isOpen;
}

bool CCTV::isOpen() const
{
	return m_isOpen;
}

void CCTV::drawSelectedRooms() const
{
    switch (m_selectedRoom)
    {
    case CCTVRoom::MainStage:
        ClearBackground(DARKGRAY);
        DrawText("MAIN STAGE", 50, 50, 30, WHITE);
        break;

    case CCTVRoom::FoodCourt:
        ClearBackground(DARKGREEN);
        DrawText("Food COURT", 50, 50, 30, WHITE);
        break;

    case CCTVRoom::GameStalls:
        ClearBackground(BROWN);
        DrawText("MAIN HALL", 50, 50, 30, WHITE);
        break;

    case CCTVRoom::MainHall:
        ClearBackground(BROWN);
        DrawText("MAIN HALL", 50, 50, 30, WHITE);
        break;

    case CCTVRoom::LeftHall:
        ClearBackground(DARKPURPLE);
        DrawText("LEFT HALL", 50, 50, 30, WHITE);
        break;

    case CCTVRoom::RightHall:
        ClearBackground(MAROON);
        DrawText("RIGHT HALL", 50, 50, 30, WHITE);
        break;

    default:
        ClearBackground(BLACK);
        DrawText("ERROR", 50, 50, 30, WHITE);
    }

}

CCTVRoom CCTV::getSelectedRoom() const
{
    return m_selectedRoom;
}

void CCTV::handleInput()
{
    for (CCTVButton& camera : m_cameraButtons)
    {
        if (camera.room == m_selectedRoom)
        {
            continue;
        }

        if (camera.button.isClicked())
        {
            selectRoom(camera.room);
            break;
        }
    }
}

void CCTV::selectRoom(const CCTVRoom& room)
{
    if (room == m_selectedRoom)
    {
        return;
    }

    m_selectedRoom = room;

    refreshButtons();

}

void CCTV::refreshButtons()
{
    for (CCTVButton& camera : m_cameraButtons)
    {
        if (camera.room == m_selectedRoom) //active room
        {
            camera.button.setBackgroundColor(BLUE);
            camera.button.setHoverColor({ 173, 216, 230, 255 });
            continue;
        }
        else
        {
            camera.button.setBackgroundColor(camera.bgColor);
            camera.button.setHoverColor(camera.hoverColor);
        }
    }
}

