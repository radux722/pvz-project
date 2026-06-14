#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>

class Zombie : public Entity
{
protected:
    float speed;
    float baseSpeed;
    int damage;
    float attackTimer;
    float attackCooldown;

    bool isSlowed;
    float slowTimer;

    sf::Texture textureNormal;
    sf::Texture textureFrozen;
    sf::Sprite sprite;

public:
    Zombie(float x, float y);

    virtual void attack();

    void move(float dt);

    void applySlow(float duration);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    sf::FloatRect getBounds() const;
    bool isDead() const;

    bool canAttack(float dt);

    int getDamage() const;

    virtual std::string getType() const = 0;

    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }

    int getHealth() const
    {
        return health;
    }

    void setHealth(int hp)
    {
        health = hp;
    }

};