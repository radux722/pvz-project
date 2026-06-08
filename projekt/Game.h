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
    sf::Text sunText;

    sf::RectangleShape peashooterButton;
    sf::RectangleShape sunflowerButton;
    sf::RectangleShape wallnutButton;

    sf::Text peashooterText;
    sf::Text sunflowerText;
    sf::Text wallnutText;

    sf::Text waveText;
    sf::Text gameOverText;

    World world;

    PlantType selectedPlant;

public:
    Game();

    void run();

    void update(float dt);
    void render();
};

