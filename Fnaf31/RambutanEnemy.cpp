#include "RambutanEnemy.h"

RambutanEnemy::RambutanEnemy(
    Room startingRoom,
    int aiLevel,
    float movementInterval)
    : Enemy(startingRoom,aiLevel,movementInterval)
{
}

void RambutanEnemy::onMovementOpportunity(const EnemyContext& context)
{
    const bool beingWatched = context.cctvOpen && context.selectedRoom == Room::GameStalls;

    if (beingWatched)
    {
        return;
    }

    if (m_currentRoom == Room::LeftDoor)
    {
        handleAttack(context);
        return;
    }

    if (m_stage < MAX_STAGE)
    {
        advanceStage();
        return;
    }

    rush();
}

EnemyType RambutanEnemy::getType() const
{
    return EnemyType::Rambutan;
}

int RambutanEnemy::getStage() const
{
    return m_stage;
}


void RambutanEnemy::advanceStage()
{
    ++m_stage;
}

void RambutanEnemy::rush()
{
    m_currentRoom = Room::LeftDoor;
}

void RambutanEnemy::handleAttack(const EnemyContext& context)
{
    if (context.leftDoorClosed)
    {
        reset();
        return;
    }

    m_hasAttacked = true;
}

void RambutanEnemy::reset()
{
    m_stage = 0;
    m_currentRoom = Room::GameStalls;
}
