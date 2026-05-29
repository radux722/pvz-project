#include "Plant.h"

Plant::Plant(float x, float y)
    : Entity(x, y, 100),
    cost(50),
    attackSpeed(1.f)
{
    shape.setSize(sf::Vector2f(60.f, 60.f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(position);
}

void Plant::update(float dt)
{
}

void Plant::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}