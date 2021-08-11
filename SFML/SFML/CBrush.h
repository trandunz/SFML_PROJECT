#pragma once
#include "CCanvas.h"
#include <iostream>
#include <list>
class CBrush
{
public:
	enum BRUSHTYPE
	{
		CIRCLE,
		TRIANGLE,
		SQUARE,
		CUSTOM,
		SPRITE
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

	void Undo();

	int m_BushSize;
	int m_Rotation;
	int m_SideCount;

private:
	sf::RenderWindow* m_RenderWindow;
	sf::Vector2f m_vMousePosition;
	CCanvas* m_Canvas;
	
};

