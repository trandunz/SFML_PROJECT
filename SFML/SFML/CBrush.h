//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CBrush.h
// Description : CBrush Header file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#pragma once
#include <iostream>
#include <list>

#include "CCanvas.h"

class CBrush
{
public:
	enum BRUSHTYPE
	{
		CIRCLE,
		TRIANGLE,
		SQUARE,
		CUSTOM,
		SPRITE,
		DEFAULT
	};

	BRUSHTYPE m_BrushType;

	CBrush(sf::RenderWindow* _renderWindow, CCanvas* _canvas);
	~CBrush();
	std::list<sf::CircleShape> PaintedBrushList;
	
	void Render();
	void Update();
	void PaintBrush();
	void SetMousePosition(sf::Vector2f Position);
	sf::Vector2f GetMousePosition();

	void SetActiveColour(sf::Color _Color);

	void Undo();

	int m_BushSize;
	int m_Rotation;
	int m_SideCount;

	sf::Color m_Colour;

private:
	sf::RenderWindow* m_RenderWindow;
	sf::Vector2f m_vMousePosition;
	CCanvas* m_Canvas;
	
};

