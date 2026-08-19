#include "JambuEnemy.h"

JambuEnemy::JambuEnemy(
    Room startingRoom,
    int aiLevel,
    float movementInterval)
    : Enemy(startingRoom,aiLevel,movementInterval)
{
    m_route =
    {
        Room::MainStage,
        Room::FoodCourt,
        Room::MainHall,
        Room::RightHall,
        Room::RightDoor
    };

    for (std::size_t i = 0; i < m_route.size(); ++i)
    {
        if (m_route[i] == startingRoom)
        {
            m_routeIndex = i;
            break;
        }
    }
}

EnemyType JambuEnemy::getType() const
{
    return EnemyType::Jambu;
}

void JambuEnemy::moveForward()
{
    if (m_routeIndex + 1 >= m_route.size())
    {
        return;
    }

    ++m_routeIndex;

    m_currentRoom = m_route[m_routeIndex];
}

void JambuEnemy::onMovementOpportunity(const EnemyContext& context)
{
    if (m_currentRoom == Room::RightDoor)
    {
        handleAttack(context);
        return;
    }

    moveForward();
}

void JambuEnemy::handleAttack(
    const EnemyContext& context
)
{
    if (context.rightDoorClosed)
    {
        retreat();
        return;
    }

    m_hasAttacked = true;
}

void JambuEnemy::retreat()
{
    m_routeIndex = 0;
    m_currentRoom = m_route[0];
}