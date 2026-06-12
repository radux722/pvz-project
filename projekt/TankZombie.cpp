#include "TankZombie.h"

TankZombie::TankZombie(float x, float y) :Zombie(x, y)
{
	health = 350;
	speed = 15.f;
	baseSpeed = 15.f;
	damage = 100;
	attackCooldown = 1.f;

	shape.setFillColor(sf::Color(100, 100, 100));
}