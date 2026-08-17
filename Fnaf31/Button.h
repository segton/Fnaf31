#pragma once
#include <string>
#include "Raylib.h"

class Button
{
public:
	bool isClicked() const;
	void draw() const;
	void setPosition(const float x, const float y);
	void setSize(const float width, float height);
	bool isHovered() const;
	void setText(const std::string& text, float fontSize);
	void setButton(
		const std::string& text, 
		const float fontSize, 
		const Rectangle& bounds,
		const Color& backgroundColor = GRAY, 
		const Color& hoverColor = LIGHTGRAY, 
		const Color& textColor = BLACK, 
		const Color& borderColor = WHITE);

private:
	Rectangle m_bounds{}; //{ position: {x,y}, size: {width, height} }
	std::string m_text{};
	bool m_isHovered = false;
	float m_fontSize = 20.0f;
	Color m_backgroundColor = GRAY;
	Color m_hoverColor = LIGHTGRAY;
	Color m_textColor = BLACK;
	Color m_borderColor = WHITE;
};

