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

void Peashooter::update(float dt)
{
    Plant::update(dt);

    shootTimer += dt;
}

bool Peashooter::canShoot() const
{
    return shootTimer >= 1.5f;
}

void Peashooter::resetShootTimer()
{
    shootTimer = 0.f;
}