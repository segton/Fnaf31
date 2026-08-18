#include "Button.h"


Button::Button(Rectangle bounds,
    const std::string& text,
    const int fontSize,
    const Color& backgroundColor,
    const Color& hoverColor,
    const Color& textColor,
    const Color& borderColor) :
    m_bounds{ bounds }, m_text{ text }, m_fontSize{fontSize}, 
    m_backgroundColor{backgroundColor}, m_hoverColor{hoverColor},
    m_textColor{textColor}, m_borderColor{borderColor}
{
}

bool Button::isHovered() const
{
	return CheckCollisionPointRec(GetMousePosition(), m_bounds);
}


bool Button::isClicked() const
{
    return isHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Button::setText(const std::string& text, int fontSize)
{
	m_text = text;
	m_fontSize = fontSize;
}


void Button::draw() const
{
    const bool hovered = isHovered();

    DrawRectangleRec(
        m_bounds,
        hovered ? m_hoverColor : m_backgroundColor);

    DrawRectangleLinesEx(
        m_bounds,
        2.0f,
        m_borderColor);

    const int textWidth = MeasureText(m_text.c_str(), m_fontSize);

    const int textX =
        static_cast<int>(
            m_bounds.x + (m_bounds.width - textWidth) / 2.0f
            );

    const int textY =
        static_cast<int>(
            m_bounds.y + (m_bounds.height - m_fontSize) / 2.0f
            );
	//center align text within the button bounds

    DrawText(
        m_text.c_str(),
        textX,
        textY,
        m_fontSize,
        m_textColor);
}

void Button::setPosition(float x, float y)
{
    m_bounds.x = x;
    m_bounds.y = y;
}

void Button::setSize(const float width, const float height)
{
    m_bounds.width = width;
    m_bounds.height = height;
}

void Button::setBackgroundColor(const Color& color)
{
    m_backgroundColor = color;
}

void Button::setHoverColor(const Color& color)
{
    m_hoverColor = color;
}