#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Plant.h"
#include "Zombie.h"
#include "Bullet.h"

#include "Peashooter.h"
#include "Sunflower.h"
#include "Wallnut.h"

#include "BasicZombie.h"
#include "FastZombie.h"

#include "Grid.h"

class World
{
private:
    std::vector<std::unique_ptr<Plant>> plants;
    std::vector<std::unique_ptr<Zombie>> zombies;
    std::vector<std::unique_ptr<Bullet>> bullets;

 
    float zombieSpawnTimer;

    int zombieKills;


    void checkCollisions();
    void spawnZombie();

    Grid grid;

    int sunPoints = 50;

    bool gameOver;
    bool gameWon;

    int plantsPlaced;
    int totalSunCollected;
    float playTime;

public:
    World();

    void update(float dt);
    void draw(sf::RenderWindow& window);
    void addPeashooter(float x, float y);
    void placePeashooter(int row, int col);

    int getZombieKills() const; // getter

    void placePlant(int row, int col, PlantType type);

    int getSunPoints() const;
    void addSunPoints(int amount) { sunPoints += amount; }

    // fale zombie
    int currentWave;
    int zombiesToSpawn;
    float waveTimer;
    float spawnTimer;
    int getCurrentWave() const;

    //lopata - usuwanie rosliny
    void removePlantAt(int row, int col);

    bool isGameOver() const;
    bool isGameWon() const;

    // zapisywanie i wczytywanie
    void saveGame(const std::string& filename);
    void loadGame(const std::string& filename);

    int getPlantsPlaced() const;
    int getTotalSunCollected() const;
    float getPlayTime() const;

};
