#include "Peashooter.h"

Peashooter::Peashooter(float x, float y)
    : Plant(x, y), shootTimer(0.f)
{
    health = 300;
    cost = 100;
    attackSpeed = 1.5;

    shape.setFillColor(sf::Color::Blue);
}

void Peashooter::attack()
{
}

bool Peashooter::canShoot(float dt)
{
    shootTimer += dt;

    if (shootTimer >= attackSpeed)
    {
        shootTimer = 0.f;
        return true;
    }

    return false;
}