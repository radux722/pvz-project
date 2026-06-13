#include "Wallnut.h"

Wallnut::Wallnut(float x, float y)
    : Plant(x, y)
{
    health = 3000;
    cost = 50;

    if (texture.loadFromFile("wallnut.png")) {
        sprite.setTexture(texture);

        //orginalny rozmiar
        sf::FloatRect bounds = sprite.getLocalBounds();

        // zmienia obrazek 85x85
        sprite.setScale(85.f / bounds.width, 85.f / bounds.height);

        sprite.setPosition(position);
    }
}

void Wallnut::attack()
{
}