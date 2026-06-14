#include "BerserkerZombie.h"

BerserkerZombie::BerserkerZombie(float x, float y)
    : Zombie(x, y), isEnraged(false)
{
    health = 250;
    baseSpeed = 20.f;
    speed = baseSpeed;
    damage = 100;
    attackCooldown = 1.0f;

    sprite.setColor(sf::Color(255, 140, 0));
}

void BerserkerZombie::update(float dt)
{
    if (!isEnraged && health <= 125)
    {
        isEnraged = true;
        baseSpeed = 70.f;

        if (!isSlowed)
        {
            speed = baseSpeed;
        }

        sprite.setColor(sf::Color(255, 0, 0));
    }

    Zombie::update(dt);
}

std::string BerserkerZombie::getType() const
{
    return "BerserkerZombie";
}