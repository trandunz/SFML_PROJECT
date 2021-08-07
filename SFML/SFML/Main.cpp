#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "CCanvas.h"
#include "CBrush.h"

namespace Utils
{
    int WINDOWHEIGHT = 800;
    int WINDOWWIDTH = 800;
}

void CentreCanvas();
void CenterBrush();
sf::View SetViewToCanvas();
void Start();
void Update();
void Render();

sf::RenderWindow* m_RenderWindow;
CCanvas* m_Canvas;
CBrush* m_Brush;



int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_RenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "IwPaint.exe", sf::Style::Default, settings);
	m_RenderWindow->setFramerateLimit((unsigned)120);
	m_Canvas = new CCanvas(m_RenderWindow, sf::Vector2f(100.0f,100.0f));
	m_Brush = new CBrush(m_RenderWindow, m_Canvas);


	Start();
	Update();

	delete m_Canvas;
	delete m_RenderWindow;
	m_Canvas = nullptr;
	m_RenderWindow = nullptr;
	return 0;
}

void Start()
{
	SetViewToCanvas();
	CentreCanvas();
	Render();
}
 
void Update()
{
	// Update Loop
	while (m_RenderWindow->isOpen())
	{
		// Undo Brush
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			m_Brush->Undo();
		}

		sf::Event event;
		while (m_RenderWindow->pollEvent(event))
		{
			// Close
			if (event.type == sf::Event::Closed)
			{
				m_RenderWindow->close();
			}

			// Resizing
			else if (event.type == sf::Event::Resized)
			{
				
				sf::Vector2f worldPos = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_Canvas->m_Canvas.getPosition()));
				sf::Vector2f worldPosB = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_Canvas->m_BackGround.getPosition()));
				
				Render();
			}

			// Left Mouse
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				
				Render();
				m_Brush->PaintBrush();
			}

			// Canvas Zoom
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

					Render();

				}
				
			}

			// Object Updates
			m_Canvas->Update();
			m_Brush->Update();

			//Render
			
		}
	}
}

void Render()
{
	m_RenderWindow->clear();

	// Object Renders
	m_Canvas->Render();
	m_Brush->Render();

	m_RenderWindow->display();
}

void CentreCanvas()
{
	/*m_Canvas->m_Canvas.setPosition(m_RenderWindow->getSize().x / 2, m_RenderWindow->getSize().y / 2);
	m_Canvas->m_BackGround.setPosition(m_RenderWindow->getSize().x / 2, m_RenderWindow->getSize().y / 2);*/
	CenterBrush();
}

void CenterBrush()
{
	m_Brush->FitToCanvas();
}

void FillBackGround()
{
	m_Canvas->m_BackGround.setScale(m_RenderWindow->getSize().x / m_Canvas->m_BackGround.getScale().x, m_RenderWindow->getSize().y / m_Canvas->m_BackGround.getScale().y);
}

sf::View SetViewToCanvas()
{
	sf::View CanvasView(m_Canvas->m_Canvas.getPosition(), sf::Vector2f(0.0f, 0.0f));
	CanvasView.setCenter(m_Canvas->m_Canvas.getPosition());
	return CanvasView;
}

//void add(sf::CircleShape shape)
//{
//	circles.push_back(shape);
//}