#include "BasicZombie.h"

BasicZombie::BasicZombie(float x, float y)
    : Zombie(x, y)
{
    health = 120;
    speed = 25.f;
    damage = 100;
    attackCooldown = 1.f;

    shape.setFillColor(sf::Color::Red);
}