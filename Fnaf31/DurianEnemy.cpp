#include "DurianEnemy.h"
#include <iostream>
#include <string>

DurianEnemy::DurianEnemy(Room startingRoom, int aiLevel, float movementInterval)
	: Enemy(startingRoom, aiLevel, movementInterval)
{ 
	m_route.reserve(4);
	m_route.push_back(Room::MainStage);
	m_route.push_back(Room::FoodCourt);
	m_route.push_back(Room::LeftHall);
	m_route.push_back(Room::LeftDoor);
}

void DurianEnemy::onMovementOpportunity(const EnemyContext& enemyContext)
{
	if (!rollMovement())
	{
		return;
	}
	
	std::cout << "Durian enemy has moved to "
		<< roomName(m_currentRoom)
		<< '\n';

	if (m_currentRoom == Room::LeftDoor)
	{
		handleAttack(enemyContext);
		return;
	}

	moveForward();
}

void DurianEnemy::handleAttack(const EnemyContext& enemyContext)
{
	if (enemyContext.leftDoorClosed)
	{
		retreat();
	}
	else
	{
		std::cout << "game over\n";
	}
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

