#pragma once
#include <vector>
#include "Room.h"
#include "EnemyContext.h"
#include "EnemyType.h"


class AudioManager;

class Enemy
{
public:
    virtual ~Enemy() = default;

	virtual void update(float dt, const EnemyContext& enemyContext);

    Room getCurrentRoom() const;
    bool isActive() const;

    virtual EnemyType getType() const = 0;

    bool hasAttacked() const { return m_hasAttacked; }

protected:
    Enemy(Room startingRoom, int aiLevel, float movementInterval, AudioManager& audioManager);

    virtual void onMovementOpportunity(const EnemyContext& enemyContext) = 0;

    virtual void handleAttack(const EnemyContext& enemyContext) = 0;

    virtual void retreat();

    bool rollMovement() const;

    void beginDoorWait();

protected:

    std::vector<Room> m_route;
    std::size_t m_routeIndex = 0;

    Room m_currentRoom;
    int m_aiLevel = 0;
    float m_movementTimer = 0.0f;
    float m_movementInterval;
    bool m_active = true;

    bool m_hasAttacked = false;

    bool m_waitingAtDoor = false;

    float m_doorTimer = 0.0f;
    float m_doorWaitDuration = 0.0f;

    AudioManager* m_audioManagerPtr;
};

