#include "Zombie.h"

Zombie::Zombie(float x, float y)
    : Entity(x, y, 100),
    speed(50.f),
    damage(10)
{
    shape.setSize(sf::Vector2f(60.f, 60.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
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