#include "BasicZombie.h"

BasicZombie::BasicZombie(float x, float y)
    : Zombie(x, y)
{
    health = 120;
    speed = 25.f;
    baseSpeed = 25.f;
    damage = 100;
    attackCooldown = 1.f;

    textureNormal.loadFromFile("basic_zombie.png");
    textureFrozen.loadFromFile("basic_zombie_frozen.png");

    sprite.setTexture(textureNormal);

    //orginalny rozmiar
    sf::FloatRect bounds = sprite.getLocalBounds();


    sprite.setScale(100.f / bounds.width, 100.f / bounds.height);

    sprite.setPosition(position);
}