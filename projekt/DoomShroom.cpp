#include "DoomShroom.h"

DoomShroom::DoomShroom(float x, float y)
    : Plant(x, y), fuseTimer(1.5f), exploded(false)
{
    health = 300;
    cost = 125;

    if (texture.loadFromFile("doomshroom.png")) {
        sprite.setTexture(texture);

        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setScale(85.f / bounds.width, 85.f / bounds.height);
        sprite.setPosition(position.x + 17.5f, position.y + 35.f);
    }
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