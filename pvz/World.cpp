#include "World.h"
#include "BasicZombie.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "Wallnut.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>


World::World() //: bulletTimer(0.f), zombieSpawnTimer(0.f)
{
    bulletTimer = 0.f;
    zombieSpawnTimer = 0.f;
    zombieKills = 0;
    sunPoints = 250;

    /*plants.push_back(
        std::make_unique<Peashooter>(200.f, 300.f)
    );
    */

    /*zombies.push_back(
        std::make_unique<BasicZombie>(1100.f, 300.f)
    );*/
   
    // fale zombie
    currentWave = 1;
    zombiesToSpawn = 5;
    waveTimer = 0.f;
    spawnTimer = 0.f;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void World::update(float dt)
{
    // logika fal i spawn zombie co 2 sek
    waveTimer += dt/2;
    spawnTimer += dt;

    if (zombiesToSpawn > 0 && spawnTimer >= 2.f)
    {
        spawnZombie();

        zombiesToSpawn--;

        spawnTimer = 0.f;
    }

    if (zombiesToSpawn == 0 && zombies.empty())
    {
        currentWave++;

        zombiesToSpawn = currentWave * 5;
    }

    
    zombieSpawnTimer += dt;

    

    /*if (zombieSpawnTimer >= 3.f)
    {
        spawnZombie();
        zombieSpawnTimer = 0.f;
    }*/
    

    for (auto& plant : plants)
    {
        plant->update(dt);
    }

    // strzelanie 
    bulletTimer += dt;
    for (auto& plant : plants)
    {
        Peashooter* peashooter =
            dynamic_cast<Peashooter*>(plant.get());

        if (peashooter && bulletTimer >= 1.f)
        {
            std::cout << "SHOT\n"; // do testu

            sf::FloatRect bounds =
                peashooter->getBounds();

            bullets.push_back(
                std::make_unique<Bullet>(
                    bounds.left + bounds.width,
                    bounds.top + bounds.height / 2.f
                )
            );
        }
    }
    if (bulletTimer >= 1.f)
    {
        bulletTimer = 0.f;
    }


    for (auto& plant : plants)
    {
        Sunflower* sunflower = dynamic_cast<Sunflower*>(plant.get());

        if (sunflower && sunflower->canProduceSun())
        {
            sunPoints += 25; //addSunPoints(25)
        }
    }

    for (auto& zombie : zombies)
    {
        bool blocked = false;

        for (auto& plant : plants)
        {
            if (zombie->getBounds().intersects(plant->getBounds()))
            {
                blocked = true;
                if (zombie->canAttack(dt)) // gryzienie co sekunde
                {
                    plant->takeDamage(100);
                }
                break;
            }
        }
        if (!blocked)
        {
            zombie->update(dt);
        }
    }
    for (auto& bullet : bullets)
    {
        bullet->update(dt);
    }


    checkCollisions();

    plants.erase(
        std::remove_if(
            plants.begin(),
            plants.end(),
            [](const auto& plant)
            {
                return plant->isDead();
            }
        ),
        plants.end()
    );
}

void World::draw(sf::RenderWindow& window)
{
    grid.draw(window);

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
    const float rows[5] =
    {
        80.f,
        200.f,
        320.f,
        440.f,
        560.f
    };

    int randomRow = std::rand() % 5;

    zombies.push_back(
        std::make_unique<BasicZombie>(
            1100.f,
            rows[randomRow]
        )
    );
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
            [this](const auto& zombie)
            {
                if (zombie->isDead())
                {
                    zombieKills++;
                    return true;
                }
                return false;
            }),
        zombies.end());


}

void World::addPeashooter(float x, float y)
{
    plants.push_back(std::make_unique<Peashooter>(x, y));
}

int World::getZombieKills() const
{
    return zombieKills;
}

void World::placePeashooter(int row, int col)
{
    if (!grid.placePlant(row, col))
        return;

    sf::Vector2f pos = grid.getCellPosition(row, col);

    plants.push_back(std::make_unique<Peashooter>(pos.x, pos.y));
}



void World::placePlant(int row, int col, PlantType type)
{
    int cost = 0;

    switch (type)
    {
    case PlantType::Peashooter:
        cost = 100;
        break;

    case PlantType::Sunflower:
        cost = 50;
        break;

    case PlantType::Wallnut:
        cost = 50;
        break;
    }

    if (sunPoints < cost)
    {
        return;
    }

    if (!grid.placePlant(row, col))
        return;

    sf::Vector2f pos = grid.getCellPosition(row, col);

    switch (type)
    {
    case PlantType::Peashooter:
        plants.push_back(
            std::make_unique<Peashooter>(pos.x, pos.y)
        );
        break;

    case PlantType::Sunflower:
        plants.push_back(
            std::make_unique<Sunflower>(pos.x, pos.y)
        );
        break;

    case PlantType::Wallnut:
        plants.push_back(
            std::make_unique<Wallnut>(pos.x, pos.y)
        );
        break;
    }

    sunPoints -= cost;
}

int World::getSunPoints() const
{
    return sunPoints;
}

int World::getCurrentWave() const
{
    return currentWave;
}