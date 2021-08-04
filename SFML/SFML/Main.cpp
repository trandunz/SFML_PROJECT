#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "CCanvas.h"

namespace Utils
{
    int WINDOWHEIGHT = 400;
    int WINDOWWIDTH = 400;
}

void CentreCanvas();
void Start();
void Update();
void Render();

sf::RenderWindow* m_RenderWindow;
CCanvas* m_Canvas;

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_RenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "SFML works!", sf::Style::Default, settings);
	m_Canvas = new CCanvas(m_RenderWindow, sf::Vector2f(100.0f,100.0f));
	Update();

	delete m_Canvas;
	delete m_RenderWindow;
	m_Canvas = nullptr;
	m_RenderWindow = nullptr;
	return 0;
}

void Start()
{
	CentreCanvas();
	Update();
}
 
void Update()
{
	while (m_RenderWindow->isOpen())
	{
		sf::Event event;
		while (m_RenderWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_RenderWindow->close();
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					m_Canvas->Zoom();
					std::cout << "wheel type: vertical" << std::endl;
				}
				std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
				std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
			}
				
		}

		m_Canvas->Update();
		Render();
		
	}
}

void Render()
{
	m_RenderWindow->clear();
	m_Canvas->Render();
	m_RenderWindow->display();
}

void CentreCanvas()
{
	
	sf::View view1;
	view1.setSize(1200.f, 800.f);
	view1.setCenter(m_Canvas->m_Canvas.getPosition());
	m_RenderWindow->setView(view1);
}