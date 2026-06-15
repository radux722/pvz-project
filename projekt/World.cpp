#include "World.h"
#include "BasicZombie.h"
#include "Peashooter.h"
#include "SnowPea.h"
#include "Sunflower.h"
#include "Wallnut.h"
#include "DoomShroom.h"
#include "TankZombie.h"
#include "BossZombie.h"
#include "BerserkerZombie.h"
#include "ZombieFactory.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
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
    plantsPlaced = 0;
    totalSunCollected = 0;
    playTime = 0.f;

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
    playTime += dt;
    waveTimer += dt/2;
    spawnTimer += dt;

    float currentSpawnInterval = std::max(0.6f, 2.5f - (currentWave * 0.2f));

    if (zombiesToSpawn > 0 && spawnTimer >= currentSpawnInterval)
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
            zombiesToSpawn = 4 + (currentWave * 2) + (currentWave * currentWave / 3);
        }
    }

    
    zombieSpawnTimer += dt;
    

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
        SnowPea* snowpea = dynamic_cast<SnowPea*>(plant.get());
        if (!snowpea) continue;

        bool zombieInRow = false;
        for (auto& zombie : zombies)
        {
            if (std::abs(zombie->getBounds().top - snowpea->getBounds().top) < 100.f)
            {
                zombieInRow = true;
                break;
            }
        }

        if (zombieInRow && snowpea->canShoot())
        {
            sf::FloatRect bounds = snowpea->getBounds();
            bullets.push_back(std::make_unique<Bullet>(
                bounds.left + bounds.width,
                bounds.top + bounds.height / 2.f,
                true
            ));
            snowpea->resetShootTimer();
        }
    }


    for (auto& plant : plants)
    {
        Sunflower* sunflower = dynamic_cast<Sunflower*>(plant.get());

        if (sunflower && sunflower->canProduceSun())
        {
            sunPoints += 25; //addSunPoints(25)
            totalSunCollected += 25;
        }
    }

    for (auto& plant : plants)
    {
        DoomShroom* shroom = dynamic_cast<DoomShroom*>(plant.get());

        if (shroom && shroom->shouldExplode())
        {
            sf::Vector2f center = shroom->getPosition();

            for (auto& zombie : zombies)
            {
                sf::Vector2f zPos = zombie->getPosition();

                float dx = center.x - zPos.x;
                float dy = center.y - zPos.y;
                float distance = std::sqrt(dx * dx + dy * dy);

                if (distance <= 300.f)
                {
                    zombie->takeDamage(2000);
                }
            }

            shroom->takeDamage(9999);
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

                plant->onZombieContact(zombie.get());

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
        130.f,
        250.f,
        370.f,
        490.f,
        610.f
    };

    int randomRow = std::rand() % 5;
    int chance = std::rand() % 100;

    float spawnY = rows[randomRow];
    float spawnX = 1050.f;

    // Sprawdzenie, czy w tym rzędzie są już zombie.
    // Jeśli tak, nowe zombie pojawi się za ostatnim.
    for (auto& zombie : zombies)
    {
        if (std::abs(zombie->getBounds().top - spawnY) < 50.f)
        {
            spawnX = std::max(
                spawnX,
                zombie->getBounds().left + 120.f
            );
        }
    }

    // Wybór typu zombie zależnie od fali
    if (currentWave <= 2)
    {
        zombies.push_back(
            std::make_unique<BasicZombie>(
                spawnX,
                spawnY
            )
        );
    }
    else if (currentWave <= 4)
    {
        if (chance < 30)
        {
            zombies.push_back(
                std::make_unique<FastZombie>(
                    spawnX,
                    spawnY
                )
            );
        }
        else if (chance < 50)
        {
            zombies.push_back(
                std::make_unique<TankZombie>(
                    spawnX,
                    spawnY
                )
            );
        }
        else if (chance < 70)
        {
            zombies.push_back(
                std::make_unique<BerserkerZombie>(
                    spawnX,
                    spawnY
                )
            );
        }
        else
        {
            zombies.push_back(
                std::make_unique<BasicZombie>(
                    spawnX,
                    spawnY
                )
            );
        }
    }
    else if (currentWave <= 7)
    {
        if (chance < 10)
        {
            zombies.push_back(
                std::make_unique<BossZombie>(
                    spawnX,
                    spawnY - 20.f
                )
            );
        }
        else if (chance < 40)
        {
            zombies.push_back(
                std::make_unique<TankZombie>(
                    spawnX,
                    spawnY
                )
            );
        }
        else if (chance < 55)
        {
            zombies.push_back(
                std::make_unique<BerserkerZombie>(
                    spawnX,
                    spawnY
                )
            );
        }
        else if (chance < 70)
        {
            zombies.push_back(
                std::make_unique<FastZombie>(
                    spawnX,
                    spawnY
                )
            );
        }
        else
        {
            zombies.push_back(
                std::make_unique<BasicZombie>(
                    spawnX,
                    spawnY
                )
            );
        }
    }
    else
    {
        if (chance < 25)
        {
            zombies.push_back(
                std::make_unique<BossZombie>(
                    spawnX,
                    spawnY - 20.f
                )
            );
        }
        else if (chance < 55)
        {
            zombies.push_back(
                std::make_unique<TankZombie>(
                    spawnX,
                    spawnY
                )
            );

        }
        else if (chance < 75)
        {
            zombies.push_back(
                std::make_unique<BerserkerZombie>(
                    spawnX,
                    spawnY
                )
            );
        }
        else if (chance < 90)
        {
            zombies.push_back(
                std::make_unique<FastZombie>(
                    spawnX,
                    spawnY
                )
            );
        }
        else
        {
            zombies.push_back(
                std::make_unique<BasicZombie>(
                    spawnX,
                    spawnY
                )
            );
        }
    }
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

                if ((*bulletIt)->getIsFreezing())
                {
                    zombie->applySlow(3.0f);
                }

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


bool World::placePlant(int row, int col, PlantType type)
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

    case PlantType::SnowPea:
        cost = 175;
        break;
    
    case PlantType::DoomShroom:
        cost = 250;
        break;
    }

    // Za mało słońca
    if (sunPoints < cost)
    {
        return false;
    }

    // Pole zajęte
    if (!grid.placePlant(row, col))
    {
        return false;
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
    case PlantType::SnowPea:
    {
        auto snow = std::make_unique<SnowPea>(pos.x, pos.y);
        snow->setGridPosition(row, col);
        plants.push_back(std::move(snow));
        break;
    }
    case PlantType::DoomShroom:
    {
        auto shroom = std::make_unique<DoomShroom>(pos.x, pos.y);
        shroom->setGridPosition(row, col);
        plants.push_back(std::move(shroom));
        break;
    }
    }

    sunPoints -= cost;
    plantsPlaced++;

    return true;
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
        else if (dynamic_cast<Wallnut*>(plant.get()))
            type = PlantType::Wallnut;
        else if (dynamic_cast<SnowPea*>(plant.get()))
            type = PlantType::SnowPea;
        else if (dynamic_cast<DoomShroom*>(plant.get()))
            type = PlantType::DoomShroom;
        else
            continue;

        file << static_cast<int>(type) << " "
            << plant->getRow() << " "
            << plant->getCol() << "\n";
    }

    file << "ZOMBIES " << zombies.size() << "\n";

    for (const auto& zombie : zombies)
    {
        file << zombie->getType() << " "
            << zombie->getPosition().x << " "
            << zombie->getPosition().y << " "
            << zombie->getHealth()
            << "\n";
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
    zombies.clear();

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

        case PlantType::SnowPea:
        {
            auto wall = std::make_unique<SnowPea>(pos.x, pos.y);
            wall->setGridPosition(row, col);
            plants.push_back(std::move(wall));
            break;
        }
        case PlantType::DoomShroom:
        {
            auto doom = std::make_unique<DoomShroom>(pos.x, pos.y);
            doom->setGridPosition(row, col);
            plants.push_back(std::move(doom));
            break;
        }
        }
    }

    std::string label;
    int zombieCount;

    file >> label >> zombieCount;   // ZOMBIES 3

    for (int i = 0; i < zombieCount; i++)
    {
        std::string type;
        float x, y;
        int hp;

        file >> type >> x >> y >> hp;

        //Użycie fabryki
        std::unique_ptr<Zombie> zombie = ZombieFactory::createZombie(type, x, y);

        if (zombie)
        {
            zombie->setHealth(hp);
            zombies.push_back(std::move(zombie));
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

int World::getPlantsPlaced() const
{
    return plantsPlaced;
}

int World::getTotalSunCollected() const
{
    return totalSunCollected;
}

float World::getPlayTime() const
{
    return playTime;
}

//lopata - usuwanie rosliny
void World::removePlantAt(int row, int col)
{
    for (auto& plant : plants)
    {
        if (plant->getRow() == row && plant->getCol() == col && !plant->isDead())
        {
            sunPoints += 25;
            plant->takeDamage(9999);           
            return;
        }
    }
}