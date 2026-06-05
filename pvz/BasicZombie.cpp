#include "BasicZombie.h"

BasicZombie::BasicZombie(float x, float y)
    : Zombie(x, y)
{
    speed = 25.f;

    shape.setFillColor(sf::Color::Red);
}