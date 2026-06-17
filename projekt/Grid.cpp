#include "Grid.h"
#include <iostream>

const float GRID_OFFSET_Y = 130.f; // 130 pixeli od gory okienka

Grid::Grid()
{
    // rozmiar komorek
    cellWidth = 120.f;
    cellHeight = 120.f;

    occupied.resize(
        ROWS,
        std::vector<bool>(COLS, false)
    );
}

// sprawdza czy mozna postawic w danym miejscu
bool Grid::placePlant(int row, int col)
{
    std::cout << "Row: " << row
        << " Col: " << col
        << std::endl;

    if (row < 0 || row >= ROWS)
        return false;

    if (col < 0 || col >= COLS)
        return false;

    if (occupied[row][col])
        return false;

    occupied[row][col] = true;

    return true;
}

// zamiana wierszy i kolumn = pixele
sf::Vector2f Grid::getCellPosition(int row, int col) const
{
    return sf::Vector2f(
        col * cellWidth + 20.f,
        row * cellHeight + GRID_OFFSET_Y
    );
}

void Grid::draw(sf::RenderWindow& window)
{
    sf::RectangleShape line;
    line.setFillColor(sf::Color::Black);

    for (int i = 0; i <= COLS; i++)
    {
        line.setSize(sf::Vector2f(2.f, ROWS * cellHeight));
        line.setPosition(
            i * cellWidth,
            GRID_OFFSET_Y
        );

        window.draw(line);
    }

    for (int i = 0; i <= ROWS; i++)
    {
        line.setSize(sf::Vector2f(COLS * cellWidth, 2.f));

        line.setPosition(
            0.f,
            GRID_OFFSET_Y + i * cellHeight
        );

        window.draw(line);
    }
}

void Grid::removePlant(int row, int col)
{
    if (row < 0 || row >= ROWS)
        return;

    if (col < 0 || col >= COLS)
        return;

    occupied[row][col] = false;
}