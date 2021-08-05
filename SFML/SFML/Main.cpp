#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "CCanvas.h"

namespace Utils
{
    int WINDOWHEIGHT = 400;
    int WINDOWWIDTH = 400;
}

void CentreCanvas();
sf::View SetViewToCanvas();
void Start();
void Update();
void Render();
void scaleToFit();

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
	Start();

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
			else if (event.type == sf::Event::Resized)
			{
				m_RenderWindow->setView(sf::View(sf::FloatRect(0.f, 0.f, m_RenderWindow->getSize().x, m_RenderWindow->getSize().y)));
				sf::Vector2f worldPos = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_Canvas->m_Canvas.getPosition()));
				CentreCanvas();
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					if (event.mouseWheelScroll.delta >= 1)
					{
						std::cout << "zoom In" << std::endl;
						m_Canvas->ZoomIn();
					}
					else if (event.mouseWheelScroll.delta <= -1)
					{
						std::cout << "zoom out" << std::endl;
						m_Canvas->ZoomOut();
					}



				}
			}


			m_Canvas->Update();
			Render();
		}
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
	m_Canvas->m_Canvas.setPosition(m_RenderWindow->getSize().x / 2, m_RenderWindow->getSize().y / 2);
}

sf::View SetViewToCanvas()
{
	sf::View CanvasView(m_Canvas->m_Canvas.getPosition(), sf::Vector2f(500.f, 500.f));
	return CanvasView;
}