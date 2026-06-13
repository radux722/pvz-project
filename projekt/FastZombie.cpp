#include "FastZombie.h"

FastZombie::FastZombie(float x, float y)
    : Zombie(x, y)
{
    health = 70; 
    speed = 40.f;
    baseSpeed = 40.f;
    damage = 80;

    attackCooldown = 0.8f;

    textureNormal.loadFromFile("fast_zombie.png");
    textureFrozen.loadFromFile("fast_zombie_frozen.png");

    sprite.setTexture(textureNormal);

    //orginalny rozmiar
    sf::FloatRect bounds = sprite.getLocalBounds();

    // zmienia obrazek 85x85
    sprite.setScale(100.f / bounds.width, 100.f / bounds.height);

    sprite.setPosition(position);
}