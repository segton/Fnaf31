#pragma once
#include "Enemy.h"
#include "Room.h"

class DurianEnemy : public Enemy
{
public:
	~DurianEnemy() override = default;

	DurianEnemy(Room startingRoom, int aiLevel, float movementInterval);
	void onMovementOpportunity(const EnemyContext& enemyContext) override;

	void handleAttack(const EnemyContext& enemyContext) override;

private:
	void moveForward();
	
};

