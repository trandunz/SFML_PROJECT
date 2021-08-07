#pragma once
#include "CCanvas.h"
#include <list>
class CBrush
{
public:
	CBrush(sf::RenderWindow* _renderWindow, CCanvas* _canvas);
	~CBrush();
	std::list<sf::CircleShape> PaintedBrushList;
	
	void Render();
	void Update();
	void PaintBrush();

	void FitToCanvas();

	void Undo();

private:
	CCanvas* m_Canvas;
	sf::RenderWindow* m_RenderWindow;
};

