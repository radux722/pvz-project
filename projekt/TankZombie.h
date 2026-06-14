#pragma once

#include "Zombie.h"

class TankZombie : public Zombie
{
public:
	TankZombie(float x, float y);

	std::string getType() const override
	{
		return "TankZombie";
	}
};
