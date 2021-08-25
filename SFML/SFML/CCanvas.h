//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CCanvas.h
// Description : CCanvas Header file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#pragma once
#pragma warning (disable : 26812) // SILENCE MINION
#include <SFML/Graphics.hpp>
#include <iostream>

class CCanvas
{
public:
	sf::Vector2f m_Size;
	sf::RectangleShape m_Canvas;
	/*sf::Image* m_CanvasImage;*/
	sf::Sprite m_BackGround;
	/*sf::Texture* m_CanvTexture;*/
	sf::Texture m_BGTexture;
	
	CCanvas();
	CCanvas(sf::RenderWindow* _window, sf::Vector2f _size);
	~CCanvas();
	void SetRenderWindow(sf::RenderWindow*);
	sf::RenderWindow* GetRenderWindow();

	void Start();
	void Update();
	virtual void Render();

protected:
	sf::RenderWindow* m_RenderWindow;
};

