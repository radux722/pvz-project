#include "Plant.h"
#include <iostream>

Plant::Plant(float x, float y)
    : Entity(x, y, 100),
    cost(50),
    attackSpeed(1.f),
    health(100)
{

}

void Plant::update(float dt)
{
}

void Plant::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect Plant::getBounds() const
{
    return sprite.getGlobalBounds();
}

void Plant::takeDamage(int damage)
{
    health -= damage;

    std::cout << "HP: " << health << std::endl;
}

bool Plant::isDead() const
{
    return health <= 0;
}

void Plant::setGridPosition(int r, int c)
{
    row = r;
    col = c;
}

int Plant::getRow() const
{
    return row;
}

int Plant::getCol() const
{
    return col;
}

//odczytywanie ceny punktow dla lopaty
int Plant::getCost() const
{
    return cost;
}