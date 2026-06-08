#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>

class Zombie : public Entity
{
protected:
    float speed;
    int damage;
    float attackTimer;
    float attackCooldown;

    sf::RectangleShape shape;

public:
    Zombie(float x, float y);

    virtual void attack();

    void move(float dt);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    sf::FloatRect getBounds() const;
    bool isDead() const;

    bool canAttack(float dt);

    int getDamage() const;

};