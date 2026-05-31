#pragma once

#include <memory>
#include <vector>

#include "Plant.h"
#include "Zombie.h"
#include "Bullet.h"

#include "Peashooter.h"
#include "Sunflower.h"
#include "Wallnut.h"

#include "BasicZombie.h"
#include "FastZombie.h"

class World
{
private:
    std::vector<std::unique_ptr<Plant>> plants;
    std::vector<std::unique_ptr<Zombie>> zombies;
    std::vector<std::unique_ptr<Bullet>> bullets;

    float bulletTimer;
    float zombieSpawnTimer;

    void checkCollisions();
    void spawnZombie();

public:
    World();

    void update(float dt);
    void draw(sf::RenderWindow& window);
    


};