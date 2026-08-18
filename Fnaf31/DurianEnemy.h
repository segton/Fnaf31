#pragma once
#include "Enemy.h"

class DurianEnemy : public Enemy
{
public:
	~DurianEnemy() override = default;

	DurianEnemy(Room startingRoom, int aiLevel, float movementInterval);
	void onMovementOpportunity() override;

};

