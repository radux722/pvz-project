#include "SnowPea.h"

SnowPea::SnowPea(float x, float y) :Plant(x, y), shootTimer(0.f)
{
	health = 300;
	cost = 175;
	attackSpeed = 1.5;

	shape.setFillColor(sf::Color(100, 150, 255));
}

void SnowPea::attack() {}

void SnowPea::update(float dt)
{
	Plant::update(dt);
	shootTimer += dt;
}

bool SnowPea::canShoot() const
{
	return shootTimer >= attackSpeed;
}

void SnowPea::resetShootTimer()
{
	shootTimer = 0.f;
}