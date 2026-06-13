#include "Bullet.h"

Bullet::Bullet(float x, float y, bool freezing):isFreezing(freezing)
{
	if (isFreezing)
	{
		texture.loadFromFile("bullet_snow.png");
	}
	else
	{
		texture.loadFromFile("bullet.png");
	}
	sprite.setTexture(texture);

	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setScale(25.f / bounds.width, 25.f / bounds.height);

	sprite.setPosition(x, y);

	speed = 400.f;
	damage = 20;
}

void Bullet::update(float dt)
{
	sprite.move(speed * dt, 0.f);
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

sf::FloatRect Bullet::getBounds() const
{
	return sprite.getGlobalBounds();
}

int Bullet::getDamage() const
{
	return damage;
}

bool Bullet::getIsFreezing() const
{
	return isFreezing;  
}
