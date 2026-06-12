#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::CircleShape shape;

	float speed;
	int damage;
	bool isFreezing;

public:
	Bullet(float x, float y, bool freezing = false);
	
	void update(float dt);
	void draw(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;
	int getDamage() const;
	bool getIsFreezing() const;
};