#include "Bullet.h"

Bullet::Bullet(float x, float y)
{
	shape.setRadius(8.f);
	shape.setFillColor(sf::Color::Cyan);
	shape.setPosition(x, y);

	speed = 400.f;
	damage = 20;
}

void Bullet::update(float dt)
{
	shape.move(speed * dt, 0.f);
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

sf::FloatRect Bullet::getBounds() const
{
	return shape.getGlobalBounds();
}

int Bullet::getDamage() const
{
	return damage;
}