#include "World.h"

World::World()
{
    plants.push_back(
        std::make_unique<Peashooter>(200.f, 300.f)
    );

    zombies.push_back(
        std::make_unique<BasicZombie>(1000.f, 300.f)
    );
}

void World::update(float dt)
{
    for (auto& plant : plants)
    {
        plant->update(dt);
    }

    for (auto& zombie : zombies)
    {
        zombie->update(dt);
    }
}

void World::draw(sf::RenderWindow& window)
{
    for (auto& plant : plants)
    {
        plant->draw(window);
    }

    for (auto& zombie : zombies)
    {
        zombie->draw(window);
    }
}