#pragma once

#include "Plant.h"

class SnowPea : public Plant
{
private:
	float shootTimer;
public:
	SnowPea(float x, float y);
	void attack() override;
	void update(float dt) override;
	bool canShoot() const;
	void resetShootTimer();
};