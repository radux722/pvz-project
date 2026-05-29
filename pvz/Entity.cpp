#include "Entity.h"

Entity::Entity(float x, float y, int hp)
    : position(x, y), health(hp)
{
}

Entity::~Entity()
{
}

void Entity::takeDamage(int damage)
{
    health -= damage;
}

sf::Vector2f Entity::getPosition() const
{
    return position;
}

int Entity::getHealth() const
{
    return health;
}