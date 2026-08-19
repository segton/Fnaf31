#include "MangosteenEnemy.h"

MangosteenEnemy::MangosteenEnemy(Room startRoom,int aiLevel,float moveInterval)
    : Enemy(startRoom, aiLevel, moveInterval)
{
    m_route =
    {
        Room::MainStage,
        Room::GameStalls,
        Room::MainHall,
        Room::LeftHall,
        Room::LeftDoor
    };
}

EnemyType MangosteenEnemy::getType() const
{
    return EnemyType::Mangosteen;
}

void MangosteenEnemy::onMovementOpportunity(const EnemyContext& context)
{
    if (m_currentRoom == Room::LeftDoor)
    {
        handleAttack(context);
        return;
    }

    moveForward();
}

void MangosteenEnemy::moveForward()
{
    if (m_routeIndex + 1 >= m_route.size())
    {
        return;
    }

    ++m_routeIndex;

    m_currentRoom =
        m_route[m_routeIndex];
}

void MangosteenEnemy::handleAttack(const EnemyContext& context)
{
    if (context.leftDoorClosed)
    {
        retreat();
        return;
    }

    m_hasAttacked = true;
}

void MangosteenEnemy::retreat()
{
    m_routeIndex = 0;
    m_currentRoom = m_route[0];
}
