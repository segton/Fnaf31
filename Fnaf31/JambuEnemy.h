#pragma once
#include <vector>
#include "Enemy.h"

class JambuEnemy : public Enemy
{
public:
    JambuEnemy(Room startRoom,int aiLevel,float moveInterval);

    EnemyType getType() const override;

protected:
    void onMovementOpportunity(const EnemyContext& context) override;

    void handleAttack(const EnemyContext& context) override;

private:
    void moveForward();
    void retreat();

private:
    std::vector<Room> m_route{};
    std::size_t m_routeIndex = 0;
};