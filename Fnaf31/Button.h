#pragma once
#include <string>
#include "Raylib.h"

class Button
{
public:
	Button() = default;

	Button(
		Rectangle bounds,
		const std::string& text,
		const int fontSize,
		const Color& backgroundColor = GRAY,
		const Color& hoverColor = LIGHTGRAY,
		const Color& textColor = BLACK,
		const Color& borderColor = WHITE);

	void draw() const;

	bool isClicked() const;
	bool isHovered() const;

	void setPosition(const float x, const float y);
	void setSize(const float width, float height);
	void setBackgroundColor(const Color& color);
	void setText(const std::string& text, int fontSize);
	void setHoverColor(const Color& color);

private:
	Rectangle m_bounds{}; //{ position: {x,y}, size: {width, height} }

	std::string m_text{};
	int m_fontSize = 20;
	Color m_textColor = BLACK;
	Color m_backgroundColor = GRAY;
	Color m_selectColor = DARKGRAY;
	Color m_hoverColor = LIGHTGRAY;

	Color m_borderColor = WHITE;
};

