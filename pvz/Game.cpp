#include "Game.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(1280, 720), "Plants vs Zombies")
{
    window.setFramerateLimit(60);

    // licznik smierci
    //font.loadFromFile("arial.ttf");
    //std::cout << std::filesystem::current_path() << std::endl;
    if (!font.loadFromFile("C:/Users/rradu/Desktop/pvz-project/pvz/assets/fonts/comic.ttf")) // to trzeba zmienic !!
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

    selectedPlant = PlantType::Peashooter;
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

        update(dt);
        render();
    }
}

void Game::update(float dt)
{
    world.update(dt);
}

void Game::render()
{
    // licznik smierci
    killText.setString("Zombie kills: " + std::to_string(world.getZombieKills()));

    window.clear(sf::Color(30, 120, 30));

    world.draw(window);

    window.draw(killText);

    window.display();

    sunText.setString(
        "Sun: " + std::to_string(world.getSunPoints())
    );

    window.draw(sunText);
    window.draw(killText);
}
