#pragma once
#include "Enemy.h"

class MangosteenEnemy : public Enemy
{
public:
    MangosteenEnemy(Room startRoom, int aiLevel, float moveInterval, AudioManager& audioManager);

    EnemyType getType() const override;

protected:
    void onMovementOpportunity(const EnemyContext& context) override;

private:
    void moveForward();
    void handleAttack(const EnemyContext& context) override;
};


