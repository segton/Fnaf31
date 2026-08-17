#pragma once
#include <string>
#include "Raylib.h"

class Button
{
public:
	bool isClicked() const;
	void draw() const;
	void setPosition(float x, float y);
	void setSize(float width, float height);
	bool isHovered() const;

private:
	Rectangle m_bounds{};
	std::string m_text{};
	bool m_isHovered = false;

};

