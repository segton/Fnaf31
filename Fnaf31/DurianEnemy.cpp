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

void DurianEnemy::onMovementOpportunity()
{
	

	if (!rollMovement())
	{
		return;
	}
	if (m_routeIndex + 1 >= m_route.size())
	{
		return;
	}

	++m_routeIndex;
	m_currentRoom = m_route[m_routeIndex];

	std::string curRoom;
	switch (m_currentRoom)
	{
	case Room::MainStage:
		curRoom = "main stage";
		break;
		
	case Room::FoodCourt:
		curRoom = "food court";
		break;
		
	case Room::LeftHall:
		curRoom = "left hall";
		break;
		
	case Room::LeftDoor:
		curRoom = "left door";
		break;
	default:
		curRoom = "???";
	}

	std::cout << "Durian enemy has moved to " << curRoom << '\n';



}

