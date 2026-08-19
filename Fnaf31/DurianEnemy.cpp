#include "DurianEnemy.h"
#include <iostream>
#include <string>

DurianEnemy::DurianEnemy(Room startingRoom, int aiLevel, float movementInterval)
	: Enemy(startingRoom, aiLevel, movementInterval)
{ 
	m_route =
	{
		Room::MainStage,
		Room::FoodCourt,
		Room::MainHall,
		Room::RightHall,
		Room::RightDoor
	};
}

void DurianEnemy::onMovementOpportunity(
	const EnemyContext& context)
{
	const bool beingWatched =
		context.cctvOpen &&
		context.selectedRoom == m_currentRoom;

	if (beingWatched)
	{
		return;
	}

	if (m_currentRoom == Room::RightDoor)
	{
		handleAttack(context);
		return;
	}

	moveForward();
}

void DurianEnemy::handleAttack(const EnemyContext& enemyContext)
{
	if (enemyContext.rightDoorClosed)
	{
		retreat();
		return;
	}

	m_hasAttacked = true;
}

EnemyType DurianEnemy::getType() const
{
	return EnemyType::Durian;
}

void DurianEnemy::moveForward()
{
	if (m_routeIndex + 1 >= m_route.size())
	{
		return;
	}

	++m_routeIndex;
	m_currentRoom = m_route[m_routeIndex];
}

