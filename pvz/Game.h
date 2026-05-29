#pragma once

#include <SFML/Graphics.hpp>

#include "World.h"

class Game
{
private:
    sf::RenderWindow window;
    World world;

public:
    Game();

    void run();

    void update(float dt);
    void render();
};