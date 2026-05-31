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

    bulletTimer += dt;
    if (bulletTimer >= 1.f)
    {
        bulletTimer = 0.f;

        bullets.push_back(std::make_unique<Bullet>(260.f, 330.f));
    }

    for (auto& plant : plants)
    {
        plant->update(dt);
    }

    for (auto& zombie : zombies)
    {
        zombie->update(dt);
    }
    for (auto& bullet : bullets)
    {
        bullet->update(dt);
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
    for (auto& bullet : bullets)
    {
        bullet->draw(window);
    }
}