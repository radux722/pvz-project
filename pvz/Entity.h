#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
protected:
    sf::Vector2f position;
    int health;

public:
    Entity(float x = 0.f, float y = 0.f, int hp = 100);
    virtual ~Entity();

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    void takeDamage(int damage);

    sf::Vector2f getPosition() const;
    int getHealth() const;
};