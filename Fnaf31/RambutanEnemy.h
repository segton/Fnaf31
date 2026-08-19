#pragma once
#include "Enemy.h"

class RambutanEnemy : public Enemy
{
public:
    RambutanEnemy(
        Room startRoom,
        int aiLevel,
        float moveInterval
    );

    EnemyType getType() const override;
    int getStage() const;

protected:
    void onMovementOpportunity(const EnemyContext& context) override;

private:
    void advanceStage();
    void rush();
    void handleAttack(const EnemyContext& context) override;
    void reset();

private:
    int m_stage = 0;

    static constexpr int MAX_STAGE = 3;
};

