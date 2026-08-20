#pragma once
#include "Enemy.h"

class RambutanEnemy : public Enemy
{
public:
    RambutanEnemy(Room startRoom, int aiLevel, float moveInterval, AudioManager& audioManager);

    EnemyType getType() const override;
    int getStage() const;
    void update(float dt, const EnemyContext& enemyContext) override;

protected:
    void onMovementOpportunity(const EnemyContext& context) override;

    void retreat() override;

private:
    void advanceStage();
    void rush();
    void handleAttack(const EnemyContext& context) override;
    void reset();
    float getRushProgress() const;

private:
    int m_stage = 0;

    bool m_rushing = false;

    float m_rushTimer = 0.0f;
    float m_rushDuration = 0.8f;

    static constexpr int MAX_STAGE = 3;
};

