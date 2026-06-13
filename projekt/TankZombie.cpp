#include "TankZombie.h"

TankZombie::TankZombie(float x, float y) :Zombie(x, y)
{
	health = 350;
	speed = 15.f;
	baseSpeed = 15.f;
	damage = 100;
	attackCooldown = 1.f;

	textureNormal.loadFromFile("tank_zombie.png");
	textureFrozen.loadFromFile("tank_zombie_frozen.png");

	sprite.setTexture(textureNormal);

	//orginalny rozmiar
	sf::FloatRect bounds = sprite.getLocalBounds();

	// zmienia obrazek 85x85
	sprite.setScale(125.f / bounds.width, 125.f / bounds.height);

	sprite.setPosition(position);
}