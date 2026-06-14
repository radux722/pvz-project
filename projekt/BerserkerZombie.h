#pragma once

#include "Zombie.h"

class BerserkerZombie : public Zombie
{
private:
	bool isEnraged;
public:
	BerserkerZombie(float x, float y);

	void update(float dt) override;

	std::string getType() const override;
};
