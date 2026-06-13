#include "Peashooter.h"

Peashooter::Peashooter(float x, float y)
    : Plant(x, y), shootTimer(0.f)
{
    health = 300;
    cost = 100;
    attackSpeed = 1.5;

    if (texture.loadFromFile("peashooter.png")) {
        sprite.setTexture(texture);

        //orginalny rozmiar
        sf::FloatRect bounds = sprite.getLocalBounds();

        // zmienia obrazek 85x85
        sprite.setScale(85.f / bounds.width, 85.f / bounds.height);

        sprite.setPosition(position);
    }
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