#pragma once

#include "Entity.h"

class Zombie : public Entity
{
protected:
    float speed;
    int damage;

    sf::RectangleShape shape;

public:
    Zombie(float x, float y);

    virtual void attack();

    void move();

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};