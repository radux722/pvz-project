#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>

enum class PlantType
{
    Peashooter, Sunflower, Wallnut, SnowPea, DoomShroom
};

class Plant : public Entity
{
protected:
    int cost;
    float attackSpeed;
    int health;

    int row;
    int col;

    sf::Texture texture;
    sf::Sprite sprite;

public:
    Plant(float x, float y);

    virtual void attack() = 0;

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

    sf::FloatRect getBounds() const;

    void takeDamage(int damage);
    bool isDead() const;

    void setGridPosition(int r, int c);
    int getRow() const;
    int getCol() const;

    //odczytywanie ceny punktow dla lopaty
    int getCost() const;
};