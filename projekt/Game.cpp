#include "Game.h"
#include <iostream>
#include <filesystem>
#include <stdexcept>

Game::Game()
    : window(sf::VideoMode(1280, 720), "Plants vs Zombies"),
    selectedPlant(PlantType::Peashooter)
{
    window.setFramerateLimit(60);

    // licznik smierci
    //font.loadFromFile("arial.ttf");
    std::cout << std::filesystem::current_path() << std::endl;
    if (!font.loadFromFile("assets/fonts/comic.ttf")) // to trzeba zmienic !!
    {
        throw std::runtime_error("Krytyczny blad: Nie udalo sie zaladowac czcionki comic.ttf!");
    }
    else
    {
        std::cout << "Czcionka zaladowana" << std::endl;
    }

    killText.setFont(font);
    killText.setCharacterSize(28);
    killText.setFillColor(sf::Color::White);
    killText.setPosition(20.f, 10.f);
    sunText.setFont(font);
    sunText.setCharacterSize(28);
    sunText.setFillColor(sf::Color::Yellow);
    sunText.setPosition(20.f, 45.f);

    // gui roslin
   
    peashooterButton.setSize(sf::Vector2f(150.f, 60.f));
    peashooterButton.setPosition(240.f, 10.f);
    peashooterButton.setFillColor(sf::Color(100, 200, 100));

    sunflowerButton.setSize(sf::Vector2f(150.f, 60.f));
    sunflowerButton.setPosition(400.f, 10.f);
    sunflowerButton.setFillColor(sf::Color(220, 220, 100));

    wallnutButton.setSize(sf::Vector2f(150.f, 60.f));
    wallnutButton.setPosition(560.f, 10.f);
    wallnutButton.setFillColor(sf::Color(160, 100, 50));

    snowpeaButton.setSize(sf::Vector2f(150.f, 60.f));
    snowpeaButton.setPosition(720.f, 10.f);
    snowpeaButton.setFillColor(sf::Color(100, 150, 255));

    doomButton.setSize(sf::Vector2f(150.f, 60.f));
    doomButton.setPosition(880.f, 10.f);
    doomButton.setFillColor(sf::Color(80, 0, 80));

    peashooterText.setFont(font);
    peashooterText.setCharacterSize(20);
    peashooterText.setString("Pea (100)");
    peashooterText.setPosition(255.f, 25.f);

    sunflowerText.setFont(font);
    sunflowerText.setCharacterSize(20);
    sunflowerText.setString("Sun (50)");
    sunflowerText.setPosition(425.f, 25.f);

    wallnutText.setFont(font);
    wallnutText.setCharacterSize(20);
    wallnutText.setString("Wall (50)");
    wallnutText.setPosition(585.f, 25.f);

    snowpeaText.setFont(font);
    snowpeaText.setCharacterSize(20);
    snowpeaText.setString("Snow (175)");
    snowpeaText.setPosition(740.f, 25.f);

    doomText.setFont(font);
    doomText.setCharacterSize(20);
    doomText.setString("Doom (250)");
    doomText.setPosition(895.f, 25.f);

    // fale zombie
    waveText.setFont(font);
    waveText.setCharacterSize(28);
    waveText.setFillColor(sf::Color::Red);
    waveText.setPosition(20.f, 80.f);

    // game over
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(72);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(350.f, 220.f);

    // statystki
    statisticsText.setFont(font);
    statisticsText.setCharacterSize(30);
    statisticsText.setFillColor(sf::Color::White);
    statisticsText.setPosition(320.f, 320.f);

    // game won
    winText.setFont(font);
    winText.setCharacterSize(72);
    winText.setFillColor(sf::Color::Yellow);
    winText.setString("YOU WIN!");
    winText.setPosition(340.f, 220.f);

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
    saveButton.setPosition(1100.f, 20.f);
    saveButton.setFillColor(sf::Color(80, 80, 200));

    saveText.setFont(font);
    saveText.setString("SAVE");
    saveText.setCharacterSize(24);
    saveText.setPosition(1120.f, 30.f);

    loadButtonGame.setSize({ 120.f,50.f });
    loadButtonGame.setPosition(1100.f, 85.f);
    loadButtonGame.setFillColor(sf::Color(80, 160, 200));

    loadGameText.setFont(font);
    loadGameText.setString("LOAD");
    loadGameText.setCharacterSize(24);
    loadGameText.setPosition(1120.f, 95.f);

    // pauza
    pauseButton.setSize({ 120.f, 50.f });
    pauseButton.setPosition(1100.f, 150.f);
    pauseButton.setFillColor(sf::Color(200, 140, 60));
    pauseText.setPosition(1125.f, 150.f);

    pauseText.setFont(font);
    pauseText.setString("PAUSE");
    pauseText.setCharacterSize(24);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(1120.f, 160.f);
    
    
    pausedText.setFont(font);
    pausedText.setCharacterSize(72);
    pausedText.setFillColor(sf::Color::White);
    pausedText.setString("PAUSED");
    pausedText.setPosition(350.f, 300.f);


    // wyjscie do menu
    menuButton.setSize({ 250.f, 60.f });
    menuButton.setPosition(415.f, 420.f);
    menuButton.setFillColor(sf::Color(180, 80, 80));

    menuButtonText.setFont(font);
    menuButtonText.setString("MENU");
    menuButtonText.setCharacterSize(30);
    menuButtonText.setFillColor(sf::Color::White);
    menuButtonText.setPosition(475.f, 432.f);


    //selectedPlant = PlantType::Peashooter;



    shovelText.setFont(font);
    shovelText.setCharacterSize(20);
    shovelText.setString("Shovel");
    shovelText.setPosition(1130.f, 645.f);

    isShovelSelected = false;

    //zerowanie cooldownu
    peashooterCooldown = 0.f;
    sunflowerCooldown = 0.f;
    wallnutCooldown = 0.f;
    snowpeaCooldown = 0.f;
    doomCooldown = 0.f;

    // textury tla i lopaty
    if (backgroundTexture.loadFromFile("ground.png")) {
        backgroundSprite.setTexture(backgroundTexture);
        sf::FloatRect bounds = backgroundSprite.getLocalBounds();
        backgroundSprite.setScale(1280.f / bounds.width, 720.f / bounds.height);
    }

    if (shovelTexture.loadFromFile("shovel.png")) {
        shovelSprite.setTexture(shovelTexture);

        sf::FloatRect bounds = shovelSprite.getLocalBounds();
        shovelSprite.setScale(100.f / bounds.width, 100.f / bounds.height);

        shovelSprite.setPosition(1135.f, 625.f);
    }

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
                // zmiana pixeli ekranu na kordy w grze
                sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
                sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
                
                // ===== MENU PAUZY =====
                if (paused)
                {
                    if (pauseButton.getGlobalBounds().contains(mousePos))
                    {
                        paused = false;
                        continue;
                    }

                    if (menuButton.getGlobalBounds().contains(mousePos))
                    {
                        paused = false;
                        
                        //world = World(); do startowania od nowa

                        state = GameState::MainMenu;
                        continue;
                    }
                    continue;
                }


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
                if (shovelSprite.getGlobalBounds().contains(mousePos))
                {
                    isShovelSelected = true;
                    continue;
                }

                if (peashooterButton.getGlobalBounds().contains(mousePos))
                {
                    selectedPlant = PlantType::Peashooter;
                    isShovelSelected = false;
                    continue;
                }

                if (snowpeaButton.getGlobalBounds().contains(mousePos))
                {
                    selectedPlant = PlantType::SnowPea;
                    isShovelSelected = false;
                    continue;
                }

                if (sunflowerButton.getGlobalBounds().contains(mousePos))
                {
                    selectedPlant = PlantType::Sunflower;
                    isShovelSelected = false;
                    continue;
                }

                if (wallnutButton.getGlobalBounds().contains(mousePos))
                {
                    selectedPlant = PlantType::Wallnut;
                    isShovelSelected = false;
                    continue;
                }

                if (doomButton.getGlobalBounds().contains(mousePos))
                {
                    selectedPlant = PlantType::DoomShroom;
                    continue;
                }

                // ================= SADZENIE ROŚLIN / KOPANIE =================
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    // sadzenie na podstawie mousepos
                    //int row = (static_cast<int>((mousePos.y) - 110.f) / 120.f);
                    //int col = static_cast<int>(mousePos.x) / 120.f;
                    const float GRID_OFFSET_Y = 110.f;

                    int row = static_cast<int>((mousePos.y - GRID_OFFSET_Y) / 120.f);
                    int col = static_cast<int>(mousePos.x / 120.f);

                    if (isShovelSelected)
                    {
                        world.removePlantAt(row, col);
                        isShovelSelected = false; // Po wykopaniu odznacz lopate
                    }
                    else
                    {
                        // spr czy jest cooldown
                        bool canPlace = false;
                        if (selectedPlant == PlantType::Peashooter && peashooterCooldown <= 0.f) canPlace = true;
                        if (selectedPlant == PlantType::Sunflower && sunflowerCooldown <= 0.f) canPlace = true;
                        if (selectedPlant == PlantType::Wallnut && wallnutCooldown <= 0.f) canPlace = true;
                        if (selectedPlant == PlantType::SnowPea && snowpeaCooldown <= 0.f) canPlace = true;
                        if (selectedPlant == PlantType::DoomShroom && doomCooldown <= 0.f) canPlace = true;

                        // jesli nie ma szadzimy
                        if (canPlace)
                        {
                            // jesli jest miejsce i slonce to sadzi
                            if (world.placePlant(row, col, selectedPlant))
                            {
                                if (selectedPlant == PlantType::Peashooter) peashooterCooldown = 2.5f;
                                if (selectedPlant == PlantType::Sunflower) sunflowerCooldown = 2.5f;
                                if (selectedPlant == PlantType::Wallnut) wallnutCooldown = 2.5f;
                                if (selectedPlant == PlantType::SnowPea) snowpeaCooldown = 2.5f;
                                if (selectedPlant == PlantType::DoomShroom) doomCooldown = 5.0f;
                            }
                        }
                    }
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

                if (event.key.code == sf::Keyboard::Num4)
                    selectedPlant = PlantType::SnowPea;

                if (event.key.code == sf::Keyboard::Num5)
                    selectedPlant = PlantType::DoomShroom;

                if (world.isGameOver() || world.isGameWon())
                {
                    world = World();

                    state = GameState::MainMenu;

                    paused = false;
                }

                //zmienia stan lopaty na wylaczona
                if (event.key.code == sf::Keyboard::Num1) {
                    selectedPlant = PlantType::Peashooter;
                    isShovelSelected = false;
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

    // podswietlanie wybranej rosliny lub lopaty
    peashooterButton.setOutlineThickness(0);
    sunflowerButton.setOutlineThickness(0);
    wallnutButton.setOutlineThickness(0);
    snowpeaButton.setOutlineThickness(0);
    doomButton.setOutlineThickness(0);
    shovelSprite.setColor(sf::Color::White);

    if (isShovelSelected)
    {
        shovelSprite.setColor(sf::Color(255, 255, 255, 128));
    }
    else
    {
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

        case PlantType::SnowPea:
            snowpeaButton.setOutlineThickness(3);
            snowpeaButton.setOutlineColor(sf::Color::White);
            break;

        case PlantType::DoomShroom:
            doomButton.setOutlineThickness(3);
            doomButton.setOutlineColor(sf::Color::White);
            break;
        }
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

    // Odliczanie cooldownu
    if (peashooterCooldown > 0.f) peashooterCooldown -= dt;
    if (sunflowerCooldown > 0.f) sunflowerCooldown -= dt;
    if (wallnutCooldown > 0.f) wallnutCooldown -= dt;
    if (snowpeaCooldown > 0.f) snowpeaCooldown -= dt;
    if (doomCooldown > 0.f) doomCooldown -= dt;

    // cooldown kolor na ciemniejszy
    if (peashooterCooldown > 0.f) peashooterButton.setFillColor(sf::Color(80, 120, 80));
    else peashooterButton.setFillColor(sf::Color(100, 200, 100)); //zielony

    if (sunflowerCooldown > 0.f) sunflowerButton.setFillColor(sf::Color(140, 140, 80));
    else sunflowerButton.setFillColor(sf::Color(220, 220, 100)); //zolty

    if (wallnutCooldown > 0.f) wallnutButton.setFillColor(sf::Color(110, 80, 50));
    else wallnutButton.setFillColor(sf::Color(160, 100, 50)); //brazowy

    if (snowpeaCooldown > 0.f) snowpeaButton.setFillColor(sf::Color(80, 100, 150));
    else snowpeaButton.setFillColor(sf::Color(100, 150, 255)); //niebieski

    if (doomCooldown > 0.f) doomButton.setFillColor(sf::Color(40, 0, 40));
    else doomButton.setFillColor(sf::Color(80, 0, 80));

}

void Game::render()
{
    // menu
    if (state == GameState::MainMenu)
    {
        window.clear(sf::Color(30, 120, 30));
        window.draw(backgroundSprite);
        //world.draw(window);
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
    window.draw(backgroundSprite);
    world.draw(window);

    window.draw(sunText);
    window.draw(killText);
    window.draw(waveText);

    // rysowanie gui
    window.draw(peashooterButton);
    window.draw(sunflowerButton);
    window.draw(wallnutButton);
    window.draw(snowpeaButton);
    window.draw(doomButton);
    window.draw(peashooterText);
    window.draw(sunflowerText);
    window.draw(wallnutText);
    window.draw(snowpeaText);
    window.draw(doomText);

    // Rysowanie łopaty
    window.draw(shovelSprite);
    window.draw(shovelText);

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
        window.draw(menuButton);
        window.draw(menuButtonText);
    }

   

    window.display();

  
}
