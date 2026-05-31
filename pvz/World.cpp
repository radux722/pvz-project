#include "World.h"
#include "BasicZombie.h"
#include <algorithm>

World::World() //: bulletTimer(0.f), zombieSpawnTimer(0.f)
{
    bulletTimer = 0.f;
    zombieSpawnTimer = 0.f;
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
    zombieSpawnTimer += dt;

    if (bulletTimer >= 1.f)
    {
        bullets.push_back(std::make_unique<Bullet>(180.f, 330.f));
        bulletTimer = 0.f;
    }

    if (zombieSpawnTimer >= 3.f)
    {
        spawnZombie();
        zombieSpawnTimer = 0.f;
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

    checkCollisions();
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

void World::spawnZombie()
{
    zombies.push_back(std::make_unique<BasicZombie>(1100.f, 300.f));
}

void World::checkCollisions()
{
    for (auto bulletIt = bullets.begin();
        bulletIt != bullets.end();)
    {
        bool bulletDestroyed = false;

        for (auto& zombie : zombies)
        {
            if ((*bulletIt)->getBounds().intersects(
                zombie->getBounds()))
            {
                zombie->takeDamage(
                    (*bulletIt)->getDamage()
                );

                bulletDestroyed = true;
                break;
            }
        }

        if (bulletDestroyed)
        {
            bulletIt = bullets.erase(bulletIt);
        }
        else
        {
            ++bulletIt;
        }
    }

    zombies.erase(
        std::remove_if(
            zombies.begin(),
            zombies.end(),
            [](const auto& zombie)
            {
                return zombie->isDead();
            }),
        zombies.end());
}