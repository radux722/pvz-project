#include "Sunflower.h"

Sunflower::Sunflower(float x, float y)
    : Plant(x, y)
{
    health = 250;
    cost = 50;

    if (texture.loadFromFile("sunflower.png")) {
        sprite.setTexture(texture);

        //orginalny rozmiar
        sf::FloatRect bounds = sprite.getLocalBounds();

        // zmienia obrazek 85x85
        sprite.setScale(85.f / bounds.width, 85.f / bounds.height);

        sprite.setPosition(position);
    }
    sunTimer= 0.f;
}

void Sunflower::attack()
{
}

void Sunflower::update(float dt)
{
    sunTimer += dt;
    
}

bool Sunflower::canProduceSun()
{
    if(sunTimer >= 5.f)
    {
        sunTimer = 0.f;
        return true;
    }
    return false;
}
