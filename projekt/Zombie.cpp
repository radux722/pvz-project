#include "Zombie.h"

Zombie::Zombie(float x, float y)
    : Entity(x, y, 100),
    speed(25.f),
    baseSpeed(25.f),
    damage(100),
    attackTimer(0.f),
    attackCooldown(1.f),
    isSlowed(false),
    slowTimer(0.f)
{
    shape.setSize(sf::Vector2f(60.f, 60.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
}

void Zombie::applySlow(float duration)
{
    isSlowed = true;
    slowTimer = duration;
    speed = baseSpeed * 0.5f;
    shape.setFillColor(sf::Color(100, 100, 255));
}

void Zombie::attack()
{
}

void Zombie::move(float dt)
{
    position.x -= speed * dt;
    shape.setPosition(position);
}

void Zombie::update(float dt)
{
    if (isSlowed)
    {
        slowTimer -= dt;
        if (slowTimer <= 0.f)
        {
            isSlowed = false;
            speed = baseSpeed;
            shape.setFillColor(sf::Color::Red);
        }
    }
    move(dt);
}

void Zombie::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::FloatRect Zombie::getBounds() const
{
    return shape.getGlobalBounds();
}

bool Zombie::isDead() const
{
    return health <= 0;
}

bool Zombie::canAttack(float dt)
{
    attackTimer += dt;

    if (attackTimer >= attackCooldown)
    {
        attackTimer = 0.f;
        return true;
    }

    return false;
}

int Zombie::getDamage() const
{
    return damage;
}