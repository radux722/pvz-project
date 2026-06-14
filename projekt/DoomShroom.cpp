#include "DoomShroom.h"

DoomShroom::DoomShroom(float x, float y)
    : Plant(x, y), fuseTimer(1.5f), exploded(false)
{
    health = 300;
    cost = 125;

    sprite.setColor(sf::Color(80, 0, 80));
}

void DoomShroom::attack() {}

void DoomShroom::update(float dt)
{
    Plant::update(dt);

    // Odliczanie zapalnika
    if (fuseTimer > 0.f)
    {
        fuseTimer -= dt;
    }
    else
    {
        exploded = true;
    }
}

bool DoomShroom::shouldExplode() const
{
    return exploded;
}