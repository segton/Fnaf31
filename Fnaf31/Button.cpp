#include "Button.h"

bool Button::isHovered() const
{
	return CheckCollisionPointRec(GetMousePosition(), m_bounds);
}

bool Button::isClicked() const
{
    return isHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Button::draw() const
{
    const bool hovered =
        CheckCollisionPointRec(GetMousePosition(), m_bounds);

    DrawRectangleRec(
        m_bounds,
        hovered ? LIGHTGRAY : GRAY
    );

    DrawRectangleLinesEx(
        m_bounds,
        2.0f,
        WHITE
    );

    const int fontSize = 20;
    const int textWidth = MeasureText(m_text.c_str(), fontSize);

    const int textX =
        static_cast<int>(
            m_bounds.x + (m_bounds.width - textWidth) / 2.0f
            );

    const int textY =
        static_cast<int>(
            m_bounds.y + (m_bounds.height - fontSize) / 2.0f
            );

    DrawText(
        m_text.c_str(),
        textX,
        textY,
        fontSize,
        BLACK
    );
}

void Button::setPosition(float x, float y)
{
    m_bounds.x = x;
    m_bounds.y = y;
}

void Button::setSize(float width, float height)
{
    m_bounds.width = width;
    m_bounds.height = height;
}