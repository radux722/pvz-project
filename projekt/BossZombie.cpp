#include "BossZombie.h"

BossZombie::BossZombie(float x, float y) :Zombie(x, y)
{
	health = 800;
	speed = 10.f;
	baseSpeed = 10.f;
	damage = 300;
	attackCooldown = 1.5f;

	textureNormal.loadFromFile("boss_zombie.png");
	textureFrozen.loadFromFile("boss_zombie_frozen.png");

	sprite.setTexture(textureNormal);

	//orginalny rozmiar
	sf::FloatRect bounds = sprite.getLocalBounds();


	sprite.setScale(150.f / bounds.width, 150.f / bounds.height);

	sprite.setPosition(position);
}