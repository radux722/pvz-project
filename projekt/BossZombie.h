#pragma once

#include "Zombie.h"

class BossZombie : public Zombie
{
public:
	BossZombie(float x, float y);

	std::string getType() const override
	{
		return "BossZombie";
	}
};
