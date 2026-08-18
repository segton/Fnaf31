#include "Enemy.h"
#include "Random.h"

void Enemy::update(float dt, const EnemyContext& enemyContext)
{
	if (!m_active) return;

	m_movementTimer += dt;

	if (m_movementTimer >= m_movementInterval)
	{
		m_movementTimer = 0.0f;
		onMovementOpportunity(enemyContext);
	}
}

Enemy::Enemy(Room startingRoom, int aiLevel, float movementInterval)
    : m_currentRoom(startingRoom),
		m_aiLevel(aiLevel),
		m_movementInterval(movementInterval),
		m_movementTimer(0.0f),
		m_active(true)
{
}

void Enemy::retreat()
{
	m_routeIndex = 0;
	m_currentRoom = m_route[m_routeIndex];
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