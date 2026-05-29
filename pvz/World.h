#pragma once

#include <memory>
#include <vector>

#include "Plant.h"
#include "Zombie.h"

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

public:
    World();

    void update(float dt);
    void draw(sf::RenderWindow& window);
};