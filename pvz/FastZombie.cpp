#include "FastZombie.h"

FastZombie::FastZombie(float x, float y)
    : Zombie(x, y)
{
    speed = 80.f;

    shape.setFillColor(sf::Color::Magenta);
}