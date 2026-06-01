#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Grid
{
private:
    static const int ROWS = 5;
    static const int COLS = 9;

    float cellWidth;
    float cellHeight;

    std::vector<std::vector<bool>> occupied;

public:
    Grid();

    bool placePlant(int row, int col);

    sf::Vector2f getCellPosition(int row, int col) const;

    void draw(sf::RenderWindow& window);
};