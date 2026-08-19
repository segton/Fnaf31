#pragma once
#include <vector>
#include "Room.h"
#include "EnemyContext.h"
#include "EnemyType.h"

class Enemy
{
public:
    virtual ~Enemy() = default;

	void update(float dt, const EnemyContext& enemyContext);

    Room getCurrentRoom() const;
    bool isActive() const;

    virtual EnemyType getType() const = 0;

protected:
    Enemy(Room startingRoom, int aiLevel, float movementInterval);

    virtual void onMovementOpportunity(const EnemyContext& enemyContext) = 0;

    virtual void handleAttack(const EnemyContext& enemyContext) = 0;

    virtual void retreat();

    bool rollMovement() const;

protected:

    std::vector<Room> m_route;
    std::size_t m_routeIndex = 0;

    Room m_currentRoom;
    int m_aiLevel = 0;
    float m_movementTimer = 0.0f;
    float m_movementInterval;
    bool m_active = true;

    bool m_hasAttacked = false;
};

