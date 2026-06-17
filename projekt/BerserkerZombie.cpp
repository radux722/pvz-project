#include "BerserkerZombie.h"

BerserkerZombie::BerserkerZombie(float x, float y)
    : Zombie(x, y), isEnraged(false)
{
    health = 250;
    baseSpeed = 20.f;
    speed = baseSpeed;
    damage = 100;
    attackCooldown = 1.0f;

    textureNormal.loadFromFile("berserker_zombie.png");
    textureFrozen.loadFromFile("berserker_zombie_frozen.png");
    textureEnraged.loadFromFile("berserker_zombie_enrage.png");
    textureEnragedFrozen.loadFromFile("berserker_zombie_enrage_frozen.png");

    sprite.setTexture(textureNormal);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setScale(110.f / bounds.width, 110.f / bounds.height);
    sprite.setPosition(position);
}


void BerserkerZombie::update(float dt)
{
    if (!isEnraged && health <= 125)
    {
        isEnraged = true;
        baseSpeed = 70.f;

        if (!isSlowed)
        {
            speed = baseSpeed;
        }

        textureNormal = textureEnraged;
        textureFrozen = textureEnragedFrozen;

        if (isSlowed) {
            sprite.setTexture(textureFrozen);
        }
        else {
            sprite.setTexture(textureNormal);
        }
    }

    Zombie::update(dt);
}

std::string BerserkerZombie::getType() const
{
    return "BerserkerZombie";
}