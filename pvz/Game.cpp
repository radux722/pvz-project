#include "Game.h"

Game::Game()
    : window(sf::VideoMode(1280, 720), "Plants vs Zombies")
{
    window.setFramerateLimit(60);
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
    window.clear(sf::Color(30, 120, 30));

    world.draw(window);

    window.display();
}