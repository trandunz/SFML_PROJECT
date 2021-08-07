#include "CBrush.h"

CBrush::CBrush(sf::RenderWindow* _renderWindow, CCanvas* _canvas)
{
	m_Canvas = _canvas;
	m_RenderWindow = _renderWindow;
}

CBrush::~CBrush()
{
	while (PaintedBrushList.size() > 0)
	{
		PaintedBrushList.pop_front();
	}
	m_Canvas = nullptr;
	m_RenderWindow = nullptr;
}

void CBrush::Render()
{
	for (const sf::CircleShape& stroke : PaintedBrushList)
	{
		m_RenderWindow->draw(stroke);
		sf::Vector2f worldPosC = m_RenderWindow->mapPixelToCoords(sf::Vector2i(stroke.getPosition()));
	}
}

void CBrush::Update()
{
	FitToCanvas();
}

void CBrush::PaintBrush()
{
	float x = (float)sf::Mouse::getPosition((*m_RenderWindow)).x;

	float y = (float)sf::Mouse::getPosition(*m_RenderWindow).y;

	std::cout << x << std::endl;
	std::cout << y << std::endl;

	sf::Vector2f XY = { x,y };

	if (m_Canvas->m_Canvas.getGlobalBounds().contains(XY)) 
	{
		int r = 255;
		int g = 0;
		int b = 255;

		sf::CircleShape stroke(2);
		stroke.setOrigin(m_RenderWindow->getPosition().x, m_RenderWindow->getPosition().y);
		stroke.setPosition(x, y);
		stroke.setFillColor(sf::Color(r, g, b));
		/*stroke.setPosition(m_RenderWindow->getSize().x / 2, m_RenderWindow->getSize().y / 2);*/
		
		PaintedBrushList.push_front(stroke);
	}
	

	
}

void CBrush::FitToCanvas()
{
	for (sf::CircleShape& stroke : PaintedBrushList)
	{
		/*stroke.setScale(sf::Vector2f(m_Canvas->m_Canvas.getScale().x / stroke.getScale().x, m_Canvas->m_Canvas.getScale().y / stroke.getScale().y));*/
		stroke.setPosition(stroke.getPosition().x - (m_RenderWindow->getSize().x / 2), stroke.getPosition().y -(m_RenderWindow->getSize().y / 2));
	}
	
}

void CBrush::Undo()
{
	while (PaintedBrushList.size() > 0)
	{
		PaintedBrushList.pop_front();
	}
}
