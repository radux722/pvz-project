#include "Game.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(1280, 720), "Plants vs Zombies")
{
    window.setFramerateLimit(60);

    // licznik smierci
    //font.loadFromFile("arial.ttf");
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
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
                    world.addPeashooter(
                        static_cast<float>(event.mouseButton.x),
                        static_cast<float>(event.mouseButton.y)
                    );
                }
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
}