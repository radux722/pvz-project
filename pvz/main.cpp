#include <iostream>

#include <SFML/Graphics.hpp>

int main()
{
    std::cout << "dziallaaa" << std::endl;
    sf::RenderWindow window(sf::VideoMode(400, 400), "Test SFML 2.6.2 dzia³a!");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    shape.setPosition(100.f, 100.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(shape);

        window.display();
    }

    return 0;
}
