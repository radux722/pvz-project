#include "FastZombie.h"

FastZombie::FastZombie(float x, float y)
    : Zombie(x, y)
{
    health = 70; 
    speed = 40.f;
    damage = 80;

    attackCooldown = 0.8f;

    shape.setFillColor(sf::Color::Magenta);
}