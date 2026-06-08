#include "Game.h"
#include <iostream>
#include <filesystem>

Game::Game()
    : window(sf::VideoMode(1280, 720), "Plants vs Zombies")
{
    window.setFramerateLimit(60);

    // licznik smierci
    //font.loadFromFile("arial.ttf");
    std::cout << std::filesystem::current_path() << std::endl;
    if (!font.loadFromFile("assets/fonts/comic.ttf")) // to trzeba zmienic !!
    {
        std::cout << "Blad ladowania czcionki!" << std::endl;
    }
    else
    {
        std::cout << "Czcionka zaladowana" << std::endl;
    }
    killText.setFont(font);
    killText.setCharacterSize(28);
    killText.setFillColor(sf::Color::White);
    killText.setPosition(20.f, 20.f);
    sunText.setFont(font);
    sunText.setCharacterSize(28);
    sunText.setFillColor(sf::Color::Yellow);
    sunText.setPosition(20.f, 60.f);

    // gui roslin
    peashooterButton.setSize(sf::Vector2f(150.f, 60.f));
    peashooterButton.setPosition(300.f, 10.f);
    peashooterButton.setFillColor(sf::Color(100, 200, 100));

    sunflowerButton.setSize(sf::Vector2f(150.f, 60.f));
    sunflowerButton.setPosition(470.f, 10.f);
    sunflowerButton.setFillColor(sf::Color(220, 220, 100));

    wallnutButton.setSize(sf::Vector2f(150.f, 60.f));
    wallnutButton.setPosition(640.f, 10.f);
    wallnutButton.setFillColor(sf::Color(160, 100, 50));

    peashooterText.setFont(font);
    peashooterText.setCharacterSize(20);
    peashooterText.setString("Pea (100)");
    peashooterText.setPosition(315.f, 25.f);

    sunflowerText.setFont(font);
    sunflowerText.setCharacterSize(20);
    sunflowerText.setString("Sun (50)");
    sunflowerText.setPosition(495.f, 25.f);

    wallnutText.setFont(font);
    wallnutText.setCharacterSize(20);
    wallnutText.setString("Wall (50)");
    wallnutText.setPosition(665.f, 25.f);

    // fale zombie
    waveText.setFont(font);
    waveText.setCharacterSize(28);
    waveText.setFillColor(sf::Color::Red);
    waveText.setPosition(20.f, 100.f);

    // game over
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(72);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");

    gameOverText.setPosition(350.f, 300.f);

    //selectedPlant = PlantType::Peashooter;
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos(
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y)
                );
              
                // gui nie stawia od razu rosliny
                if (peashooterButton.getGlobalBounds().contains(mousePos))
                {
                    selectedPlant = PlantType::Peashooter;
                    continue;
                }

                if (sunflowerButton.getGlobalBounds().contains(mousePos))
                {
                    selectedPlant = PlantType::Sunflower;
                    continue;
                }

                if (wallnutButton.getGlobalBounds().contains(mousePos))
                {
                    selectedPlant = PlantType::Wallnut;
                    continue;
                }

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    int row = (mouseY - 80) / 120;
                    int col = mouseX / 120;

                    world.placePlant(row, col, selectedPlant);

                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                    selectedPlant = PlantType::Peashooter;

                if (event.key.code == sf::Keyboard::Num2)
                    selectedPlant = PlantType::Sunflower;

                if (event.key.code == sf::Keyboard::Num3)
                    selectedPlant = PlantType::Wallnut;
            }
        }

        if (!world.isGameOver())
        {
            update(dt);
        }
        render();
    }
}

void Game::update(float dt)
{
    // licznik smierci
    killText.setString("Zombie kills: " + std::to_string(world.getZombieKills()));
    
    sunText.setString("Sun: " + std::to_string(world.getSunPoints()));

    // podswietlanie wybranej rosliny
    peashooterButton.setOutlineThickness(0);
    sunflowerButton.setOutlineThickness(0);
    wallnutButton.setOutlineThickness(0);
    switch (selectedPlant)
    {
    case PlantType::Peashooter:
        peashooterButton.setOutlineThickness(3);
        peashooterButton.setOutlineColor(sf::Color::White);
        break;

    case PlantType::Sunflower:
        sunflowerButton.setOutlineThickness(3);
        sunflowerButton.setOutlineColor(sf::Color::White);
        break;

    case PlantType::Wallnut:
        wallnutButton.setOutlineThickness(3);
        wallnutButton.setOutlineColor(sf::Color::White);
        break;
    }

    // licznik fal
    waveText.setString(
        "Wave: " +
        std::to_string(world.getCurrentWave())
    );

    world.update(dt);
}

void Game::render()
{
    

    window.clear(sf::Color(30, 120, 30));

    world.draw(window);

    window.draw(sunText);
    window.draw(killText);
    window.draw(waveText);

    // rysowanie gui
    window.draw(peashooterButton);
    window.draw(sunflowerButton);
    window.draw(wallnutButton);
    window.draw(peashooterText);
    window.draw(sunflowerText);
    window.draw(wallnutText);
    
    if (world.isGameOver())
    {
        window.draw(gameOverText);
    }



    window.display();

  
}
