#pragma once

#include <SFML/Graphics.hpp>

#include "World.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text killText;
    World world;

public:
    Game();

    void run();

    void update(float dt);
    void render();
};