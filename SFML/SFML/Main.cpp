#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
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

Player* pPlayer;

void Start();
void Update();

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_rRenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "SFML works!", sf::Style::Default, settings);
	sf::CircleShape* Brush = new sf::CircleShape(1.0f);
    clClock = sf::Clock();
	
	/*Start();*/
    pPlayer = new Player(m_rRenderWindow);
	
    m_rRenderWindow = nullptr;
	Brush = nullptr;
	pPlayer = nullptr;


    return 0;
}

void Start()
{
	Brush.setFillColor(sf::Color::White);
	Brush.setRadius(30.0f);
	Brush.setOrigin(sf::Vector2f(0.0f, 0.0f));
	Brush.setPosition(10.0f, 10.0f);
	Update();
}

void Update()
{
    while (m_rRenderWindow->isOpen())
    {
		std::cout << "Brush Drawn" << std::endl;
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
			m_rRenderWindow->clear();
			/*m_rRenderWindow->draw(pPlayer->m_oPlayerBody);*/
			m_rRenderWindow->draw(Brush);
			std::cout << "Brush Drawn" << std::endl;
			m_rRenderWindow->display();
        }
    }
}

void Render(sf::RenderWindow* _renderWindow)
{
	_renderWindow->clear();
	_renderWindow->display();
}
