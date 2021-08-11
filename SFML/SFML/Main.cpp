#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "CCanvas.h"
#include "CBrush.h"
#include "CButtons.h"

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
sf::RenderWindow* m_UIWindow;
sf::View CanvasView;
CCanvas* m_Canvas;
CBrush* m_Brush;

CButtons* m_SquareButton;
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
	m_UIWindow = new sf::RenderWindow(sf::VideoMode(Utils::TOOLDWIDTH, Utils::TOOLSHEIGHT), "Tools", (sf::Style::Titlebar), settings);
	m_RenderWindow->setFramerateLimit((unsigned)120);
	m_Canvas = new CCanvas(m_RenderWindow, sf::Vector2f(100.0f,100.0f));
	m_Brush = new CBrush(m_RenderWindow, m_Canvas);
	m_ZoomFactor = 10;

	m_SquareButton = new CButtons(m_UIWindow);
	m_SquareButton->SetLabel("Square");
	//m_CircleButton = new CButtons(m_UIWindow);
	//m_SquareButton->SetLabel("Circle");
	//m_TriangleButton = new CButtons(m_UIWindow);
	//m_TriangleButton->SetLabel("Triangle");


	Start();
	Update();

	delete m_SquareButton;
	delete m_Canvas;
	delete m_RenderWindow;
	delete m_UIWindow;
	m_SquareButton = nullptr;
	m_Canvas = nullptr;
	m_RenderWindow = nullptr;
	m_UIWindow = nullptr;
	return 0;
}

void Start()
{
	m_RenderWindow->setView(SetViewToCanvas());
	
	m_Brush->m_BushSize = 4;
	m_Brush->m_SideCount = 12;
	m_Brush->m_Rotation = 0.0f;
	m_Brush->m_BrushType = m_Brush->BRUSHTYPE::CUSTOM;
	m_SquareButton->SetPosition(m_UIWindow->getSize().x / 2, m_UIWindow->getSize().y / 2);
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
			/*m_ButtonTest->bIsinBounds(m_ButtonTest->GetMousePosition());*/

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
				m_UIWindow->close();
			}

			// Resizing
			if (event.type == sf::Event::Resized)
			{
				m_ZoomFactor = 10.0f;
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
					if (event.mouseWheelScroll.delta >= 1 )
					{
						std::cout << "zoom In" << std::endl;
						CanvasView.zoom(1 - 0.1);
						CanvasView.setCenter(m_Canvas->m_Canvas.getPosition());
						m_RenderWindow->setView(CanvasView);
						/*m_Canvas->m_Canvas.setScale(m_Canvas->m_Canvas.getScale() / )*/
						m_ZoomFactor++;
					}
					else if (event.mouseWheelScroll.delta <= -1 && m_ZoomFactor > 0)
					{
						std::cout << "zoom out" << std::endl;
						CanvasView.zoom(1 + 0.1);
						CanvasView.setCenter(m_Canvas->m_Canvas.getPosition());
						m_RenderWindow->setView(CanvasView);
						//m_ButtonTest->Sprite.setScale(sf::Vector2f(m_ButtonTest->Sprite.getScale().x + m_ButtonTest->Sprite.getScale().x, m_ButtonTest->Sprite.getScale().y + m_ButtonTest->Sprite.getScale().x));
						m_ZoomFactor--;
					}
					
					Render();
					

				}
				
			}

			// Object Updates
			m_Canvas->Update();
			m_Brush->Update();
			
			

			//Render
			
		}
		while (m_UIWindow->pollEvent(event))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (m_SquareButton->bIsinBounds(m_SquareButton->GetMousePosition()))
				{
					m_Brush->m_BrushType = m_Brush->BRUSHTYPE::SQUARE;
				}
				
			}
			// Object Updates
			m_SquareButton->Update();
			//Render
			
			RenderUI();
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

void RenderUI()
{
	m_UIWindow->clear();
	m_SquareButton->Render();
	m_UIWindow->display();
}

sf::Vector2f GetMousePosition()
{
	return m_Brush->GetMousePosition();
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

