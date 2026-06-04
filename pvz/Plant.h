#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>

enum class PlantType
{
    Peashooter, Sunflower, Wallnut
};

class Plant : public Entity
{
protected:
    int cost;
    float attackSpeed;
    int health;

    sf::RectangleShape shape;

public:
    Plant(float x, float y);

    virtual void attack() = 0;

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    sf::FloatRect getBounds() const;

    void takeDamage(int damage);
    bool isDead() const;
};