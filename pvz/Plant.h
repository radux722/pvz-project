#pragma once

#include "Entity.h"

class Plant : public Entity
{
protected:
    int cost;
    float attackSpeed;

    sf::RectangleShape shape;

public:
    Plant(float x, float y);

    virtual void attack() = 0;

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
};