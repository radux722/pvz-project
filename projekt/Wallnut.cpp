#include "Wallnut.h"

Wallnut::Wallnut(float x, float y)
    : Plant(x, y)
{
    health = 3000;
    cost = 50;

    shape.setFillColor(sf::Color(139, 69, 19));
}

void Wallnut::attack()
{
}