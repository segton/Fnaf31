#include "Enemy.h"
#include "Random.h"
#include "AudioManager.h"
#include <iostream>

void Enemy::update(float dt, const EnemyContext& enemyContext)
{
    if (!m_active || m_hasAttacked)
    {
        return;
    }

    // Enemy is already at the door.
    // Do not run movement logic here
    if (m_waitingAtDoor)
    {
        m_doorTimer += dt;

        if (m_doorTimer >= m_doorWaitDuration)
        {
            std::cout << "Door wait finished\n";

            m_waitingAtDoor = false;

            handleAttack(enemyContext);
        }

        return;
    }

    //Normal movement logic
    m_movementTimer += dt;

    if (m_movementTimer < m_movementInterval)
    {
        return;
    }

    m_movementTimer = 0.0f;

    if (!rollMovement())
    {
        return;
    }

    onMovementOpportunity(enemyContext);
}

Enemy::Enemy(Room startingRoom, int aiLevel, float movementInterval, AudioManager& audioManager)
    : m_currentRoom(startingRoom),
    m_aiLevel(aiLevel),
    m_movementInterval(movementInterval),
    m_movementTimer(0.0f),
    m_active(true),
    m_audioManagerPtr(&audioManager)
{
}

void Enemy::retreat()
{
	m_routeIndex = 0;
	m_currentRoom = m_route[m_routeIndex];

    m_waitingAtDoor = false;
    m_doorTimer = 0.0f;
    m_doorWaitDuration = 0.0f;

    m_audioManagerPtr->playSound("retreat");
}

bool Enemy::rollMovement() const
{
	return Random::get(1, 20) <= m_aiLevel;
}

Room Enemy::getCurrentRoom() const
{
	return m_currentRoom;
}

bool Enemy::isActive() const
{
	return m_active;
}

void Enemy::beginDoorWait()
{
    m_waitingAtDoor = true;
    m_doorTimer = 0.0f;

    m_doorWaitDuration = static_cast<float>(GetRandomValue(1, 3));
    std::cout
        << "Door wait started: "
        << m_doorWaitDuration
        << '\n';

}

