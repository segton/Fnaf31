#pragma once
#include "Enemy.h"
#include "Room.h"

class DurianEnemy : public Enemy
{
public:
	~DurianEnemy() override = default;

	DurianEnemy(Room startRoom, int aiLevel, float moveInterval, AudioManager& audioManager);
	void onMovementOpportunity(const EnemyContext& enemyContext) override;

	void handleAttack(const EnemyContext& enemyContext) override;

	EnemyType getType() const override;

private:
	void moveForward();
	
};

