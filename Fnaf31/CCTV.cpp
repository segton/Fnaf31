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

}

void CCTV::update(float dt)
{
    for (CCTVButton& camera : m_cameraButtons)
    {
        if (camera.room == m_selectedRoom)
        {
            continue;
        }

        if (camera.button.isClicked())
        {
            m_selectedRoom = camera.room;
        }
    }
}

void CCTV::draw() const
{
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
