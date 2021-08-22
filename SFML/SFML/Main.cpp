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
sf::Vector2f GetMousePosition();

sf::RenderWindow* m_RenderWindow;
CPopOutMenu* m_PopOutMenu;
sf::View CanvasView;
//CButtons* m_CircleButton;
//CButtons* m_TriangleButton;

float m_ZoomFactor;

bool dragging = false;
sf::Vector2f startPos;

bool m_bDoOnce;

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 10;

    m_RenderWindow = new sf::RenderWindow(sf::VideoMode(Utils::WINDOWWIDTH, Utils::WINDOWHEIGHT), "IwPaint.exe", (sf::Style::Default), settings);
	m_RenderWindow->setFramerateLimit((unsigned)120);
	m_PopOutMenu = new CPopOutMenu(m_RenderWindow);
	m_ZoomFactor = 10;

	
	//m_CircleButton = new CButtons(m_UIWindow);
	//m_SquareButton->SetLabel("Circle");
	//m_TriangleButton = new CButtons(m_UIWindow);
	//m_TriangleButton->SetLabel("Triangle");

	m_bDoOnce = true;
	Start();
	Update();
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
		while (m_RenderWindow->pollEvent(event))
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

			// mIDDLE mOUSE
			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				
				if (m_PopOutMenu->m_bBrushMenu)
				{
					if (!dragging)
					{
						startPos = CanvasView.getCenter();
						std::cout << startPos.x << "----"  << startPos.y << std::endl;
						dragging = true;
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
						std::cout << "zoom In" << std::endl;
						CanvasView.zoom(1.0f - 0.1f);
						CanvasView.setCenter(m_PopOutMenu->m_Canvas->m_Canvas.getPosition());
						m_RenderWindow->setView(CanvasView);
						/*m_Canvas->m_Canvas.setScale(m_Canvas->m_Canvas.getScale() / )*/
						m_ZoomFactor++;
					}
					else if (event.mouseWheelScroll.delta <= -1 && m_ZoomFactor > 0)
					{
						std::cout << "zoom out" << std::endl;
						CanvasView.zoom(1.0f + 0.1f);
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
			m_PopOutMenu->m_Shape->Update();
			
			

			//Render
			

			
		}
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

