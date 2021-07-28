#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Player.h"

namespace Utils
{
    int WINDOWHEIGHT = 800;
    int WINDOWWIDTH = 800;
}

float m_fFPS = 60.0f;
sf::Clock clClock;
sf::RenderWindow* m_rRenderWindow;
sf::CircleShape Brush;
bool redraw;

void Update();

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_rRenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "SFML works!", sf::Style::Default, settings);
    Brush = sf::CircleShape(1.0f);
    clClock = sf::Clock();
    Brush.setFillColor(sf::Color::White);
    Brush.setOrigin(sf::Vector2f(0.0f, 0.0f));
    Brush.setPosition(200.0f, 200.0f);

    Player* pPlayer = new Player(m_rRenderWindow);
    Update();

    m_rRenderWindow = nullptr;


    return 0;
}

void Update()
{
    while (m_rRenderWindow->isOpen())
    {

        if (clClock.getElapsedTime().asSeconds() >= 1.0f / m_fFPS)
        {
            redraw = true; //We're ready to redraw everything
            clClock.restart();
        }
        else //Sleep until next 1/60th of a second comes around
        {
            sf::Time sleepTime = sf::seconds((1.0f / m_fFPS) - clClock.getElapsedTime().asSeconds());
            sleep(sleepTime);
        }

        sf::Event event;
        while (m_rRenderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_rRenderWindow->close();
        }

        if (redraw)
        {
            redraw = false;
            m_rRenderWindow->draw(Brush);
            m_rRenderWindow->display();
        }
    }
}