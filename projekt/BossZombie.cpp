#include "BossZombie.h"

BossZombie::BossZombie(float x, float y) :Zombie(x, y)
{
	health = 800;
	speed = 10.f;
	baseSpeed = 10.f;
	damage = 300;
	attackCooldown = 1.5f;

	shape.setSize(sf::Vector2f(80.f, 80.f));

	shape.setFillColor(sf::Color::Black);
}