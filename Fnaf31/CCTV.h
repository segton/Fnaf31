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

class CCTV
{
public:

    void init();
	void update(float dt);
	void draw() const;
    void isOpen();
private:
	bool m_isOpen = false;
	std::vector<Button> m_cameraButtons{};

    Button m_testButton{};


};