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
sf::View CanvasView;
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
	m_RenderWindow->setView(SetViewToCanvas());
	Render();
}
 
void Update()
{
	// Update Loop
	while (m_RenderWindow->isOpen())
	{
		
		

		sf::Event event;
		while (m_RenderWindow->pollEvent(event))
		{
			// Undo Brush
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				m_Brush->Undo();
				Render();
			}

			// Close
			if (event.type == sf::Event::Closed)
			{
				m_RenderWindow->close();
			}

			// Resizing
			else if (event.type == sf::Event::Resized)
			{
				CanvasView = sf::View((sf::FloatRect(0.0f, 0.0f, event.size.width / 2, event.size.height / 2)));
				sf::Vector2f worldPos = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_Canvas->m_Canvas.getPosition()));
				sf::Vector2f worldPosB = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_Canvas->m_BackGround.getPosition()));
				CanvasView.setCenter(m_Canvas->m_Canvas.getPosition());
				m_RenderWindow->setView(CanvasView);
				
				Render();
			}

			// Left Mouse
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_Brush->PaintBrush();
				Render();
				
			}

			// Canvas Zoom
			if (event.type == sf::Event::MouseWheelScrolled)
			{

				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					if (event.mouseWheelScroll.delta >= 1)
					{
						std::cout << "zoom In" << std::endl;
						CanvasView.zoom(0.9);
						m_RenderWindow->setView(CanvasView);
					}
					else if (event.mouseWheelScroll.delta <= -1)
					{
						std::cout << "zoom out" << std::endl;
						CanvasView.zoom(1.1);
						m_RenderWindow->setView(CanvasView);
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

void FillBackGround()
{
	m_Canvas->m_BackGround.setScale(m_RenderWindow->getSize().x / m_Canvas->m_BackGround.getScale().x, m_RenderWindow->getSize().y / m_Canvas->m_BackGround.getScale().y);
}

sf::View SetViewToCanvas()
{
	CanvasView = sf::View(sf::FloatRect(0.0f , 0.0f, m_RenderWindow->getSize().x, m_RenderWindow->getSize().y));
	CanvasView.setCenter(m_Canvas->m_Canvas.getPosition());
	return CanvasView;
}