#pragma once

#include <SFML/Graphics.hpp>

#include "World.h"
#include "Plant.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text killText;
    World world;

    PlantType selectedPlant;

public:
    Game();

    void run();

    void update(float dt);
    void render();
};

