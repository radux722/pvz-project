#include "DoomShroom.h"
#include "Zombie.h"

DoomShroom::DoomShroom(float x, float y)
    : Plant(x, y), exploded(false)
{
    health = 300;
    cost = 250;

    if (texture.loadFromFile("doomshroom.png")) {
        sprite.setTexture(texture);

        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setScale(85.f / bounds.width, 85.f / bounds.height);
        sprite.setPosition(position);
    }
}

void DoomShroom::attack() {}

void DoomShroom::update(float dt)
{
    Plant::update(dt);
}

bool DoomShroom::shouldExplode() const
{
    return exploded;
}

void DoomShroom::triggerExplosion()
{
    exploded = true;
}

void DoomShroom::onZombieContact(Zombie* zombie)
{
    triggerExplosion();
}