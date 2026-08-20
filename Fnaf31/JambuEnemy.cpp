#include "JambuEnemy.h"

JambuEnemy::JambuEnemy(
    Room startingRoom,int aiLevel,
    float movementInterval,AudioManager& audioManager)
    : Enemy(startingRoom,aiLevel,movementInterval, audioManager)
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

    if (m_currentRoom == Room::RightDoor)
    {
        beginDoorWait();
    }

}

void JambuEnemy::onMovementOpportunity(const EnemyContext& context)
{
    (void)context;
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
