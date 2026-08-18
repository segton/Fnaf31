#pragma once
#include "Room.h"
#include <vector>

class Enemy
{
public:
    virtual ~Enemy() = default;

	void update(float dt);

    Room getCurrentRoom() const;
    bool isActive() const;

protected:
    Enemy(Room startingRoom, int aiLevel, float movementInterval);

    virtual void onMovementOpportunity() = 0;

    bool rollMovement() const;

    std::vector<Room> m_route;
    std::size_t m_routeIndex = 0;

    Room m_currentRoom;
    int m_aiLevel = 0;
    float m_movementTimer = 0.0f;
    float m_movementInterval;
    bool m_active = true;
};

