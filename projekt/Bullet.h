#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::CircleShape shape;

	float speed;
	int damage;

public:
	Bullet(float x, float y);
	
	void update(float dt);
	void draw(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;
	int getDamage() const;
};