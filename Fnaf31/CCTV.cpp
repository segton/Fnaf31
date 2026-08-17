#include "CCTV.h"
#include <iostream>

void CCTV::init()
{
	m_testButton.setPosition(100.0f, 100.0f);
	m_testButton.setSize(200.0f, 50.0f);
}

void CCTV::update(float dt)
{
	if (m_testButton.isClicked())
	{
		std::cout << "Test button clicked!" << std::endl;
	}
}

void CCTV::draw() const
{
	m_testButton.draw();

	for (const Button& button : m_cameraButtons)
	{
		button.draw();
	}
}

void CCTV::isOpen()
{
}
