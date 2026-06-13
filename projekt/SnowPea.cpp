#include "SnowPea.h"

SnowPea::SnowPea(float x, float y) :Plant(x, y), shootTimer(0.f)
{
	health = 300;
	cost = 175;
	attackSpeed = 1.5;

	if (texture.loadFromFile("snowpea.png")) {
		sprite.setTexture(texture);

		//orginalny rozmiar
		sf::FloatRect bounds = sprite.getLocalBounds();

		// zmienia obrazek 85x85
		sprite.setScale(85.f / bounds.width, 85.f / bounds.height);

		sprite.setPosition(position);
	}
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