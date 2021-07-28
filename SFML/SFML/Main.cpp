#include <SFML/Graphics.hpp>
#include <Windows.h>

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!", sf::Style::Default, settings);
    

    sf::CircleShape circle(100.f); // circle
    sf::RectangleShape square(sf::Vector2f(100, 100)); // square

    circle.setFillColor(sf::Color::Green);
    circle.setPointCount(100);
    

    square.setPosition(250, 250);
    circle.setPosition(50, 50);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(circle);
        window.draw(square);
        window.display();
    }

    return 0;
}