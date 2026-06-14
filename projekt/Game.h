#pragma once

#include <SFML/Graphics.hpp>

#include "World.h"
#include "Plant.h"

class Game
{
private:
    PlantType selectedPlant = PlantType::Peashooter;

    sf::RenderWindow window;
    sf::Font font;
    sf::Text killText;
    sf::Text sunText;

    sf::RectangleShape peashooterButton;
    sf::RectangleShape sunflowerButton;
    sf::RectangleShape wallnutButton;
    sf::RectangleShape snowpeaButton;

    sf::Text peashooterText;
    sf::Text sunflowerText;
    sf::Text wallnutText;
    sf::Text snowpeaText;

    sf::Text waveText;
    sf::Text gameOverText;
    sf::Text winText;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    //lopata
    sf::Texture shovelTexture;
    sf::Sprite shovelSprite;
    sf::Text shovelText;
    bool isShovelSelected;

    //cooldown
    float peashooterCooldown;
    float sunflowerCooldown;
    float wallnutCooldown;
    float snowpeaCooldown;

    enum class GameState // menu
    {
        MainMenu,
        Playing,
        Paused
    };
    GameState state;
    sf::RectangleShape startButton;
    sf::RectangleShape loadButton;
    sf::RectangleShape exitButton;
    sf::Text titleText;
    sf::Text startText;
    sf::Text loadText;
    sf::Text exitText;

    sf::RectangleShape saveButton;
    sf::RectangleShape loadButtonGame;
    sf::RectangleShape pauseButton;
    sf::Text saveText;
    sf::Text loadGameText;
    sf::Text pauseText;

    sf::Text pausedText;

    sf::Text statisticsText;

    sf::RectangleShape menuButton;
    sf::Text menuButtonText;

    World world;

    //PlantType selectedPlant;
    
    bool paused;

public:
    Game();

    void run();

    void update(float dt);
    void render();
};

