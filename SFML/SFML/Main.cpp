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

bool m_bDoOnce = true;

/// <summary>
/// Main Function For Main Implementation File.
/// </summary>
/// <returns></returns>
int main()
{
	// HWND
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

	// Context Settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 10;

	// Essentials Creation 
    m_RenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "IwPaint.exe", (sf::Style::Default), settings);
	m_PopOutMenu = new CPopOutMenu(m_RenderWindow);
	
	// Essentials Startup Tweak
	m_RenderWindow->setFramerateLimit((unsigned)120);
	m_ZoomFactor = 10;

	
	Start();
	Update();


	// Cleanup
	delete m_PopOutMenu;
	m_PopOutMenu = nullptr;
	delete m_RenderWindow;
	m_RenderWindow = nullptr;

	return 0;
}

/// <summary>
/// Start Function For Main Implementation File (Intended To Be Called Before Update).
/// </summary>
void Start()
{
	m_PopOutMenu->Start();

	// Set RenderWindow To Look At Canvas
	m_RenderWindow->setView(SetViewToCanvas());

	// Render
	Render();
}
 
/// <summary>
/// Update Loop For Main Implementation File.
/// </summary>
void Update()
{
	// Update Loop
	while (m_RenderWindow->isOpen())
	{
		sf::Event event;
		while (m_RenderWindow->pollEvent(event)) // if(RenderWindow is active window)
		{
			// Tab Gained Focus
			if (event.type == sf::Event::GainedFocus)
			{
				Render();
			}

			// Tab Lost Focus
			if (event.type == sf::Event::LostFocus)
			{
				Render();
			}

			// Undo Brush
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				// Current Tool Check
				if (m_PopOutMenu->m_bBrushMenu)
				{
					m_PopOutMenu->m_Brush->Undo();
				}
				else if (m_PopOutMenu->m_bShapeMenu)
				{
					m_PopOutMenu->m_Shape->Undo();
				}
				
				// Render
				Render();
			}

			// Close
			if (event.type == sf::Event::Closed)
			{
				m_PopOutMenu->m_UIWindow->close();	// Error C6011 Is Lying
				m_RenderWindow->close();
				
				break;
			}

			// Resizing
			if (event.type == sf::Event::Resized)
			{
				// Reset Zoom Factor
				m_ZoomFactor = 10.0f;
				
				// Set View To Canvas (based on event)
				CanvasView = sf::View((sf::FloatRect(0.0f, 0.0f, event.size.width / 2.0f, event.size.height / 2.0f)));
				CanvasView.setCenter(m_PopOutMenu->m_Canvas->m_Canvas.getPosition());
				sf::Vector2f worldPos = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PopOutMenu->m_Canvas->m_Canvas.getPosition()));
				sf::Vector2f worldPosB = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PopOutMenu->m_Canvas->m_BackGround.getPosition()));
				m_RenderWindow->setView(CanvasView);
				
				// Render
				Render();
			}

			// Mouse Button Pressed & ShapeMenu
			if (event.type == sf::Event::MouseButtonPressed && m_PopOutMenu->m_bShapeMenu)
			{
				m_PopOutMenu->m_Shape->m_bCreatePreviewShape = true;
				
			}

			// Left Mouse
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// Paint Brush and Render
				if (m_PopOutMenu->m_bBrushMenu)
				{
					m_PopOutMenu->m_Brush->PaintBrush();
					Render();
				}
				// Paint Shape and Render
				if (m_PopOutMenu->m_bShapeMenu)
				{
					m_PopOutMenu->m_Shape->PaintShape();
					Render();
				}
			}

			// Mouse Released
			if (event.type == sf::Event::MouseButtonReleased && m_PopOutMenu->m_bShapeMenu)
			{
				// Create Actual Shape
				m_PopOutMenu->m_Shape->LetGoOfShape();

				// Render
				Render();
			}

			// Mouse Wheel Scrolled
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				// Canvas Zooming
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
					
					// Render
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

/// <summary>
/// Render Definition For Main Implementation File.
/// </summary>
void Render()
{
	m_RenderWindow->clear();

	// Object Renders
	m_PopOutMenu->m_Canvas->Render();
	m_PopOutMenu->m_Shape->Render();
	m_PopOutMenu->m_Brush->Render();

	m_RenderWindow->display();
}

/// <summary>
/// Returns The Mouse Position
/// </summary>
/// <returns></returns>
sf::Vector2f GetMousePosition()
{
	return m_PopOutMenu->m_Brush->GetMousePosition();
}

/// <summary>
/// Fill RenderWindow Background With Background Image.
/// </summary>
void FillBackGround()
{
	m_PopOutMenu->m_Canvas->m_BackGround.setScale(m_RenderWindow->getSize().x / m_PopOutMenu->m_Canvas->m_BackGround.getScale().x, m_RenderWindow->getSize().y / m_PopOutMenu->m_Canvas->m_BackGround.getScale().y);
}

/// <summary>
/// Assigns CanvasView to a new sf::View and center's it to the canvas origin.
/// </summary>
/// <returns></returns>
sf::View SetViewToCanvas()
{
	CanvasView = sf::View(sf::FloatRect(0.0f , 0.0f, m_RenderWindow->getSize().x, m_RenderWindow->getSize().y));

	CanvasView.setCenter(m_PopOutMenu->m_Canvas->m_Canvas.getPosition());

	return CanvasView;
}

