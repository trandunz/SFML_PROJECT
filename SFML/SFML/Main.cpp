//			  -----------
//			  | IwPaint	|
//			  -----------
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Main.cpp
// Description : The Main Implementation File For IwPaint.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

// Non-Local Includes
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

// Local Includes
#include "CPopOutMenu.h"

namespace Utils
{
	int WINDOWHEIGHT = 720;
	int WINDOWWIDTH = 1280;

	int TOOLSHEIGHT = 720;
	int TOOLDWIDTH = 320;
};

void Start();
void Update();
void Render();

sf::Vector2f GetMousePosition();

sf::View SetViewToCanvas();

sf::RenderWindow* m_RenderWindow;
CPopOutMenu* m_PopOutMenu;
sf::View CanvasView;
sf::Vector2f startPos;

float m_ZoomFactor;
bool dragging = false;
bool m_bDoOnce;

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 10;

    m_RenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "IwPaint.exe", (sf::Style::Default), settings);
	m_PopOutMenu = new CPopOutMenu(m_RenderWindow);
	
	m_RenderWindow->setFramerateLimit((unsigned)120);
	m_ZoomFactor = 10;
	m_bDoOnce = true;


	Start();
	Update();

	// Cleanup
	delete m_PopOutMenu;
	m_PopOutMenu = nullptr;
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
		while (m_RenderWindow->pollEvent(event)) // if(RenderWindow is active window)
		{
			// Undo Brush
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				if (m_PopOutMenu->m_bBrushMenu)
				{
					m_PopOutMenu->m_Brush->Undo();
				}
				else if (m_PopOutMenu->m_bShapeMenu)
				{
					m_PopOutMenu->m_Shape->Undo();
				}
				
				Render();
			}

			// Close
			if (event.type == sf::Event::Closed)
			{
				m_PopOutMenu->m_UIWindow->close();
				m_RenderWindow->close();
				
				break;
			}

			// Resizing
			if (event.type == sf::Event::Resized)
			{
				m_ZoomFactor = 10.0f;
				CanvasView = sf::View((sf::FloatRect(0.0f, 0.0f, event.size.width / 2.0f, event.size.height / 2.0f)));
				sf::Vector2f worldPos = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PopOutMenu->m_Canvas->m_Canvas.getPosition()));
				sf::Vector2f worldPosB = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PopOutMenu->m_Canvas->m_BackGround.getPosition()));

				CanvasView.setCenter(m_PopOutMenu->m_Canvas->m_Canvas.getPosition());
				m_RenderWindow->setView(CanvasView);
				
				Render();
			}

			if (event.type == sf::Event::MouseButtonPressed && m_PopOutMenu->m_bShapeMenu)
			{
				m_PopOutMenu->m_Shape->m_bCreatePreviewShape = true;
				
			}

			// Left Mouse
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (m_PopOutMenu->m_bBrushMenu)
				{
					m_PopOutMenu->m_Brush->PaintBrush();
					Render();
				}
				if (m_PopOutMenu->m_bShapeMenu)
				{
					m_PopOutMenu->m_Shape->PaintShape();
					Render();
				}
			}

			if (event.type == sf::Event::MouseButtonReleased && m_PopOutMenu->m_bShapeMenu)
			{
				m_PopOutMenu->m_Shape->LetGoOfShape();

				Render();
				Update();
			}

			// Middle Mouse
			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				if (m_PopOutMenu->m_bBrushMenu)
				{
					if (!dragging)
					{
						startPos = CanvasView.getCenter();
						dragging = true;

						std::cout << startPos.x << "----"  << startPos.y << std::endl;
					}
					else
					{
						dragging = false;
					}

					if (dragging)
					{
						CanvasView.setCenter(GetMousePosition().x - startPos.x, GetMousePosition().y - startPos.y);

						std::cout << "DRAGGING" << std::endl;
					}

					Render();
				}
			}
			else
			{
				dragging = false;
			}

			// Canvas Zoom
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					if (event.mouseWheelScroll.delta >= 1 )
					{
						CanvasView.zoom(1.0f - 0.1f);
						m_ZoomFactor++;

						CanvasView.setCenter(m_PopOutMenu->m_Canvas->m_Canvas.getPosition());

						m_RenderWindow->setView(CanvasView);

						std::cout << "zoom In" << std::endl;
					}
					else if (event.mouseWheelScroll.delta <= -1 && m_ZoomFactor > 0)
					{
						CanvasView.zoom(1.0f + 0.1f);
						m_ZoomFactor--;

						CanvasView.setCenter(m_PopOutMenu->m_Canvas->m_Canvas.getPosition());

						m_RenderWindow->setView(CanvasView);
						
						std::cout << "zoom out" << std::endl;
					}
					
					Render();
				}
			}

			// Object Updates if(RenderWindow is active window)
			m_PopOutMenu->m_Canvas->Update();
			m_PopOutMenu->m_Brush->Update();
			m_PopOutMenu->m_Shape->Update();
			
			// Render if(RenderWindow is active window)

		}

		// PopOutMenu Update
		if (m_PopOutMenu != nullptr)
		{
			m_PopOutMenu->Update();
			m_PopOutMenu->Render();
		}
	}
}

void Render()
{
	m_RenderWindow->clear();

	// Object Renders
	m_PopOutMenu->m_Canvas->Render();
	m_PopOutMenu->m_Shape->Render();
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

