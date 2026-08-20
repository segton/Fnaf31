#include "RambutanEnemy.h"
#include "AudioManager.h"

#include "raymath.h"

RambutanEnemy::RambutanEnemy(Room startingRoom, int aiLevel,
    float movementInterval, AudioManager& audioManager)
    : Enemy(startingRoom, aiLevel, movementInterval, audioManager)
{
}

void RambutanEnemy::update(float dt,const EnemyContext& enemyContext)
{
    if (m_rushing)
    {
        m_rushTimer += dt;

        if (m_rushTimer >= m_rushDuration)
        {
            m_rushing = false;

            m_currentRoom =
                Room::LeftDoor;

            handleAttack(enemyContext);
        }

        return;
    }

    Enemy::update(dt,enemyContext);
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
    m_rushing = true;
    m_rushTimer = 0.0f;

    m_currentRoom = Room::LeftHall;

    m_audioManagerPtr->playSound("rambutan_run");
}

float RambutanEnemy::getRushProgress() const
{
    if (!m_rushing)
    {
        return 0.0f;
    }

    return Clamp(m_rushTimer / m_rushDuration,0.0f,1.0f);
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

void RambutanEnemy::retreat()
{
    m_stage = 0;
    m_rushing = false;

    m_currentRoom =
        Room::GameStalls;

    m_audioManagerPtr->playSound("retreat");
}
