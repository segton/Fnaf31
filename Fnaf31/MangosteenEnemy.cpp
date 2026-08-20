#include "MangosteenEnemy.h"

MangosteenEnemy::MangosteenEnemy(Room startingRoom, int aiLevel,
    float movementInterval, AudioManager& audioManager)
    : Enemy(startingRoom, aiLevel, movementInterval, audioManager)
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
    (void)context;

    moveForward();
}

void MangosteenEnemy::moveForward()
{
    if (m_routeIndex + 1 >= m_route.size())
    {
        return;
    }

    ++m_routeIndex;

    m_currentRoom = m_route[m_routeIndex];

    if (m_currentRoom == Room::LeftDoor)
    {
        beginDoorWait();
    }
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
