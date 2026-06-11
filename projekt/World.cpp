#include "World.h"
#include "BasicZombie.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "Wallnut.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>


World::World() //: bulletTimer(0.f), zombieSpawnTimer(0.f)
{
    //bulletTimer = 0.f;
    zombieSpawnTimer = 0.f;
    zombieKills = 0;
    sunPoints = 200;
    gameOver = false;
    gameWon = false;

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

        if (currentWave > 10) // po 10 falach win
        {
            gameWon = true;
        }
        else
        {
            zombiesToSpawn = currentWave + 4;
        }
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
    for (auto& plant : plants)
    {
        Peashooter* peashooter =
            dynamic_cast<Peashooter*>(plant.get());

        // pomijanie nie Peashooterow
        if (!peashooter)
            continue;

        bool zombieInRow = false;
        for (auto& zombie : zombies)
        {
            /*std::cout << "Zombie: " << zombie->getBounds().top
                << " Plant: " << peashooter->getBounds().top
                << std::endl;*/

            if (std::abs(
                zombie->getBounds().top -
                peashooter->getBounds().top
            ) < 100.f)
            {
                zombieInRow = true;
                break;
            }
        }

        // strzelanie tylko gdy zombie w row
        if (zombieInRow && peashooter->canShoot())
        {
            //std::cout << "SHOT\n"; // do testu

            sf::FloatRect bounds = peashooter->getBounds();
                
            bullets.push_back(
                std::make_unique<Bullet>(
                    bounds.left + bounds.width,
                    bounds.top + bounds.height / 2.f

                )
            );
            peashooter->resetShootTimer();
        }
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
                    //plant->takeDamage(100);
                    plant->takeDamage(zombie->getDamage());
                }
                break;
            }
        }
        if (!blocked)
        {
            zombie->update(dt);

            if (zombie->getBounds().left <= 0.f)
            {
                gameOver = true;
            }
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

            [this](const auto& plant)
            {
                if (plant->isDead())
                {
                    grid.removePlant(
                        plant->getRow(),
                        plant->getCol()
                    );

                    return true;
                }

                return false;
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

    int chance = std::rand() % 100;

    if (currentWave < 3)
    {
        zombies.push_back(
            std::make_unique<BasicZombie>(
                1100.f,
                rows[randomRow]
            )
        );
    }
    else if (currentWave < 5)
    {
        if (chance < 20)
        {
            zombies.push_back(
                std::make_unique<FastZombie>(
                    1100.f,
                    rows[randomRow]
                )
            );
        }
        else
        {
            zombies.push_back(
                std::make_unique<BasicZombie>(
                    1100.f,
                    rows[randomRow]
                )
            );
        }
    }
    else
    {
        if (chance < 40)
        {
            zombies.push_back(
                std::make_unique<FastZombie>(
                    1100.f,
                    rows[randomRow]
                )
            );
        }
        else
        {
            zombies.push_back(
                std::make_unique<BasicZombie>(
                    1100.f,
                    rows[randomRow]
                )
            );
        }
    }




    /*const float rows[5] =
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
    );*/


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

int World::getZombieKills() const
{
    return zombieKills;
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

    // Za mało słońca
    if (sunPoints < cost)
    {
        return;
    }

    // Pole zajęte
    if (!grid.placePlant(row, col))
    {
        return;
    }

    sf::Vector2f pos = grid.getCellPosition(row, col);

    switch (type)
    {
    case PlantType::Peashooter:
    {
        auto pea = std::make_unique<Peashooter>(pos.x, pos.y);

        pea->setGridPosition(row, col);

        plants.push_back(std::move(pea));

        break;
    }

    case PlantType::Sunflower:
    {
        auto sun = std::make_unique<Sunflower>(pos.x, pos.y);

        sun->setGridPosition(row, col);

        plants.push_back(std::move(sun));

        break;
    }

    case PlantType::Wallnut:
    {
        auto wall = std::make_unique<Wallnut>(pos.x, pos.y);

        wall->setGridPosition(row, col);

        plants.push_back(std::move(wall));

        break;
    }
    }

    sunPoints -= cost;
}


void World::saveGame(const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
        return;

    file << sunPoints << "\n";
    file << currentWave << "\n";
    file << zombieKills << "\n";

    file << plants.size() << "\n";

    for (auto& plant : plants)
    {
        PlantType type;

        if (dynamic_cast<Peashooter*>(plant.get()))
            type = PlantType::Peashooter;
        else if (dynamic_cast<Sunflower*>(plant.get()))
            type = PlantType::Sunflower;
        else
            type = PlantType::Wallnut;

        file << static_cast<int>(type) << " "
            << plant->getRow() << " "
            << plant->getCol() << "\n";
    }

    file.close();
}

void World::loadGame(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
        return;

    plants.clear();
    zombies.clear();
    bullets.clear();

    grid = Grid();

    file >> sunPoints;
    file >> currentWave;
    file >> zombieKills;

    int plantCount;
    file >> plantCount;

    for (int i = 0; i < plantCount; i++)
    {
        int typeInt;
        int row;
        int col;

        file >> typeInt >> row >> col;

        PlantType type = static_cast<PlantType>(typeInt);

        sf::Vector2f pos = grid.getCellPosition(row, col);

        grid.placePlant(row, col);

        switch (type)
        {
        case PlantType::Peashooter:
        {
            auto pea = std::make_unique<Peashooter>(pos.x, pos.y);
            pea->setGridPosition(row, col);
            plants.push_back(std::move(pea));
            break;
        }

        case PlantType::Sunflower:
        {
            auto sun = std::make_unique<Sunflower>(pos.x, pos.y);
            sun->setGridPosition(row, col);
            plants.push_back(std::move(sun));
            break;
        }

        case PlantType::Wallnut:
        {
            auto wall = std::make_unique<Wallnut>(pos.x, pos.y);
            wall->setGridPosition(row, col);
            plants.push_back(std::move(wall));
            break;
        }
        }
    }

    file.close();
}


int World::getSunPoints() const
{
    return sunPoints;
}

int World::getCurrentWave() const
{
    return currentWave;
}

bool World::isGameOver() const
{
    return gameOver;
}

bool World::isGameWon() const
{
    return gameWon;
}