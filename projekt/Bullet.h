#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Texture texture;
	sf::Sprite sprite;

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