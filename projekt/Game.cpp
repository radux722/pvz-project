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

    // statystki
    statisticsText.setFont(font);
    statisticsText.setCharacterSize(30);
    statisticsText.setFillColor(sf::Color::White);
    statisticsText.setPosition(350.f, 380.f);

    // game won
    winText.setFont(font);
    winText.setCharacterSize(72);
    winText.setFillColor(sf::Color::Yellow);
    winText.setString("YOU WIN!");
    winText.setPosition(380.f, 300.f);

    paused = false;

    // menu
    state = GameState::MainMenu;
    titleText.setFont(font);
    titleText.setString("PLANTS VS ZOMBIES");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(300.f, 120.f);

    startButton.setSize({ 300.f, 80.f });
    startButton.setPosition(490.f, 280.f);
    startButton.setFillColor(sf::Color(80, 180, 80));

    startText.setFont(font);
    startText.setString("START");
    startText.setCharacterSize(40);
    startText.setPosition(585.f, 295.f);
   
    loadButton.setSize({ 300.f,80.f });
    loadButton.setPosition(490.f, 390.f);
    loadButton.setFillColor(sf::Color(180, 180, 80));

    loadText.setFont(font);
    loadText.setString("LOAD");
    loadText.setCharacterSize(40);
    loadText.setPosition(590.f, 405.f);

    exitButton.setSize({ 300.f,80.f });
    exitButton.setPosition(490.f, 500.f);
    exitButton.setFillColor(sf::Color(180, 80, 80));

    exitText.setFont(font);
    exitText.setString("EXIT");
    exitText.setCharacterSize(40);
    exitText.setPosition(600.f, 515.f);

    // save and load 
    saveButton.setSize({ 120.f, 50.f });
    saveButton.setPosition(1100.f, 10.f);
    saveButton.setFillColor(sf::Color(80, 80, 200));

    saveText.setFont(font);
    saveText.setString("SAVE");
    saveText.setCharacterSize(24);
    saveText.setPosition(1125.f, 20.f);

    loadButtonGame.setSize({ 120.f,50.f });
    loadButtonGame.setPosition(1100.f, 70.f);
    loadButtonGame.setFillColor(sf::Color(80, 160, 200));

    loadGameText.setFont(font);
    loadGameText.setString("LOAD");
    loadGameText.setCharacterSize(24);
    loadGameText.setPosition(1125.f, 80.f);

    // pauza
    pauseButton.setSize({ 120.f, 50.f });
    pauseButton.setPosition(1100.f, 130.f);
    pauseButton.setFillColor(sf::Color(200, 140, 60));

    pauseText.setFont(font);
    pauseText.setString("PAUSE");
    pauseText.setCharacterSize(24);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(1110.f, 140.f);
    
    pausedText.setFont(font);
    pausedText.setCharacterSize(72);
    pausedText.setFillColor(sf::Color::White);
    pausedText.setString("PAUSED");
    pausedText.setPosition(350.f, 300.f);



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

                // ================= MENU GŁÓWNE =================
                if (state == GameState::MainMenu)
                {
                    if (startButton.getGlobalBounds().contains(mousePos))
                    {
                        state = GameState::Playing;
                    }

                    if (loadButton.getGlobalBounds().contains(mousePos))
                    {
                        world.loadGame("save.txt");
                        state = GameState::Playing;
                    }

                    if (exitButton.getGlobalBounds().contains(mousePos))
                    {
                        window.close();
                    }

                    continue;
                }

                // ================= SAVE / LOAD W TRAKCIE GRY / PAUZA =================
                if (saveButton.getGlobalBounds().contains(mousePos))
                {
                    world.saveGame("save.txt");
                    std::cout << "Zapisano gre!\n";
                    continue;
                }

                if (loadButtonGame.getGlobalBounds().contains(mousePos))
                {
                    world.loadGame("save.txt");
                    std::cout << "Wczytano gre!\n";
                    continue;
                }

                if (pauseButton.getGlobalBounds().contains(mousePos))
                {
                    paused = !paused;
                    continue;
                }

                // ================= GUI ROŚLIN =================
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

                // ================= SADZENIE ROŚLIN =================
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
                if (event.key.code == sf::Keyboard::Escape)
                    paused = !paused;

                if (event.key.code == sf::Keyboard::Num1)
                    selectedPlant = PlantType::Peashooter;

                if (event.key.code == sf::Keyboard::Num2)
                    selectedPlant = PlantType::Sunflower;

                if (event.key.code == sf::Keyboard::Num3)
                    selectedPlant = PlantType::Wallnut;

                if (world.isGameOver() || world.isGameWon())
                {
                    world = World();

                    state = GameState::MainMenu;

                    paused = false;
                }

            }
        }

        if (state == GameState::Playing)
        {
            if (!world.isGameOver() &&
                !paused &&
                !world.isGameWon())
            {
                world.update(dt);
            }

            update(dt);
        }

        render();
    }
}

void Game::update(float dt)
{
    if (paused)
    {
        pauseText.setString("RESUME");
    }
    else
    {
        pauseText.setString("PAUSE");
    }

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

    if (world.isGameOver() || world.isGameWon())
    {
        int minutes =
            static_cast<int>(world.getPlayTime()) / 60;

        int seconds =
            static_cast<int>(world.getPlayTime()) % 60;

        statisticsText.setString(
            "Zombie kills: " +
            std::to_string(world.getZombieKills()) +

            "\nWaves survived: " +
            std::to_string(world.getCurrentWave()) +

            "\nPlants placed: " +
            std::to_string(world.getPlantsPlaced()) +

            "\nSun collected: " +
            std::to_string(world.getTotalSunCollected()) +

            "\nPlay time: " +
            std::to_string(minutes) + ":" +
            (seconds < 10 ? "0" : "") +
            std::to_string(seconds) +

            "\n\nPress ENTER to return to menu"
        );
    }

    //world.update(dt);
    waveText.setString(
        "Wave: " +
        std::to_string(world.getCurrentWave())
    );
}

void Game::render()
{
    // menu
    if (state == GameState::MainMenu)
    {
        window.clear(sf::Color(30, 120, 30));

        window.draw(titleText);

        window.draw(startButton);
        window.draw(loadButton);
        window.draw(exitButton);

        window.draw(startText);
        window.draw(loadText);
        window.draw(exitText);

        window.display();
        return;
    }

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

    

    // save and load
    window.draw(saveButton);
    window.draw(saveText);

    window.draw(loadButtonGame);
    window.draw(loadGameText);



    // pauza
    window.draw(pauseButton);
    window.draw(pauseText);
    
    

    if (world.isGameOver())
    {
        window.draw(gameOverText);
        window.draw(statisticsText);
    }

    if (world.isGameWon())
    {
        window.draw(winText);
        window.draw(statisticsText);
    }

    if (paused)
    {
        window.draw(pausedText);
    }

   

    window.display();

  
}
