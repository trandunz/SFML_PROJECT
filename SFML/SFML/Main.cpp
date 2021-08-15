#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "CPopOutMenu.h"

namespace Utils
{
    int WINDOWHEIGHT = 720;
    int WINDOWWIDTH = 1280;

	int TOOLSHEIGHT = 720;
	int TOOLDWIDTH = 320;
}
sf::View SetViewToCanvas();
void Start();
void Update();
void Render();
void RenderUI();
sf::Vector2f GetMousePosition();

sf::RenderWindow* m_RenderWindow;
CPopOutMenu* m_PopOutMenu;
sf::View CanvasView;
//CButtons* m_CircleButton;
//CButtons* m_TriangleButton;

float m_ZoomFactor;

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_RenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "IwPaint.exe", (sf::Style::Default), settings);
	m_RenderWindow->setFramerateLimit((unsigned)120);
	m_PopOutMenu = new CPopOutMenu(m_RenderWindow);
	m_ZoomFactor = 10;

	
	//m_CircleButton = new CButtons(m_UIWindow);
	//m_SquareButton->SetLabel("Circle");
	//m_TriangleButton = new CButtons(m_UIWindow);
	//m_TriangleButton->SetLabel("Triangle");


	Start();
	Update();

	delete m_RenderWindow;
	m_RenderWindow = nullptr;
	return 0;
}

void Start()
{
	m_PopOutMenu->Start();
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
				m_PopOutMenu->m_Brush->Undo();
				Render();
			}

			// Close
			if (event.type == sf::Event::Closed)
			{
				m_RenderWindow->close();
				m_PopOutMenu->m_UIWindow->close();
			}

			// Resizing
			if (event.type == sf::Event::Resized)
			{
				m_ZoomFactor = 10.0f;
				CanvasView = sf::View((sf::FloatRect(0.0f, 0.0f, event.size.width / 2, event.size.height / 2)));
				sf::Vector2f worldPos = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PopOutMenu->m_Canvas->m_Canvas.getPosition()));
				sf::Vector2f worldPosB = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PopOutMenu->m_Canvas->m_BackGround.getPosition()));
				CanvasView.setCenter(m_PopOutMenu->m_Canvas->m_Canvas.getPosition());
				m_RenderWindow->setView(CanvasView);
				
				Render();
			}

			// Left Mouse
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (m_PopOutMenu->m_bBrushMenu)
				{
					m_PopOutMenu->m_Brush->PaintBrush();
					Render();
				}
				
				
			}

			// Canvas Zoom
			if (event.type == sf::Event::MouseWheelScrolled)
			{

				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					if (event.mouseWheelScroll.delta >= 1 )
					{
						std::cout << "zoom In" << std::endl;
						CanvasView.zoom(1 - 0.1);
						CanvasView.setCenter(m_PopOutMenu->m_Canvas->m_Canvas.getPosition());
						m_RenderWindow->setView(CanvasView);
						/*m_Canvas->m_Canvas.setScale(m_Canvas->m_Canvas.getScale() / )*/
						m_ZoomFactor++;
					}
					else if (event.mouseWheelScroll.delta <= -1 && m_ZoomFactor > 0)
					{
						std::cout << "zoom out" << std::endl;
						CanvasView.zoom(1 + 0.1);
						CanvasView.setCenter(m_PopOutMenu->m_Canvas->m_Canvas.getPosition());
						m_RenderWindow->setView(CanvasView);
						//m_ButtonTest->Sprite.setScale(sf::Vector2f(m_ButtonTest->Sprite.getScale().x + m_ButtonTest->Sprite.getScale().x, m_ButtonTest->Sprite.getScale().y + m_ButtonTest->Sprite.getScale().x));
						m_ZoomFactor--;
					}
					
					Render();
					

				}
				
			}

			// Object Updates
			
			m_PopOutMenu->m_Canvas->Update();
			m_PopOutMenu->m_Brush->Update();
			
			

			//Render
			

			
		}
		m_PopOutMenu->Update();
		m_PopOutMenu->Render();
	}
}

void Render()
{
	m_RenderWindow->clear();

	// Object Renders
	m_PopOutMenu->m_Canvas->Render();
	m_PopOutMenu->m_Brush->Render();


	m_RenderWindow->display();
}

sf::Vector2f GetMousePosition()
{
	return m_PopOutMenu->m_Brush->GetMousePosition();
}

void FillBackGround()
{
	m_PopOutMenu->m_Canvas->m_BackGround.setScale(m_RenderWindow->getSize().x / m_PopOutMenu->m_Canvas->m_BackGround.getScale().x, m_RenderWindow->getSize().y / m_PopOutMenu->m_Canvas->m_BackGround.getScale().y);
}

sf::View SetViewToCanvas()
{
	CanvasView = sf::View(sf::FloatRect(0.0f , 0.0f, m_RenderWindow->getSize().x, m_RenderWindow->getSize().y));
	CanvasView.setCenter(m_PopOutMenu->m_Canvas->m_Canvas.getPosition());
	return CanvasView;
}

