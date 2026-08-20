#pragma once
#include <vector>
#include "Enemy.h"

class JambuEnemy : public Enemy
{
public:
    JambuEnemy(Room startRoom,int aiLevel,float moveInterval,AudioManager& audioManager);

    EnemyType getType() const override;

protected:
    void onMovementOpportunity(const EnemyContext& context) override;

    void handleAttack(const EnemyContext& context) override;

private:
    void moveForward();

};