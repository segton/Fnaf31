#include "CCTV.h"
#include <iostream>

void CCTV::init()
{
	m_testButton.setPosition(100.0f, 100.0f);
	m_testButton.setSize(200.0f, 50.0f);
	m_testButton.setText("Test Button asdadasdadadsdsa",30.f);
	
	m_testButton2.setButton("Test2", 50.f, { 200.f, 200.f, 80.f, 80.f });
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
	m_testButton2.draw();
	for (const Button& button : m_cameraButtons)
	{
		button.draw();
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
