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
	/*FitToCanvas();*/
}

void CBrush::PaintBrush()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((*m_RenderWindow));
	SetMousePosition(m_RenderWindow->mapPixelToCoords(pixelPos));
	m_vMousePosition -= sf::Vector2f(m_RenderWindow->getSize().x/2, m_RenderWindow->getSize().y/2);
	

	if (m_Canvas->m_Canvas.getGlobalBounds().contains(m_vMousePosition))
	{
		int r = 255;
		int g = 0;
		int b = 255;

		sf::CircleShape stroke(2);
		stroke.setOrigin(stroke.getGlobalBounds().width / 2, stroke.getGlobalBounds().height / 2);
		stroke.setPosition(m_Canvas->m_Canvas.getPosition());
		stroke.setFillColor(sf::Color(r, g, b));
		/*stroke.setPosition(m_RenderWindow->getSize().x / 2, m_RenderWindow->getSize().y / 2);*/
		
		/*std::cout << stroke.getPosition().x << std::endl;
		std::cout << stroke.getPosition().y << std::endl;*/
		PaintedBrushList.push_front(stroke);
	}
	

	
}

void CBrush::SetMousePosition(sf::Vector2f Position)
{
	m_vMousePosition = Position;
}

void CBrush::FitToCanvas()
{
	for (sf::CircleShape& stroke : PaintedBrushList)
	{
		/*stroke.setScale(sf::Vector2f(m_Canvas->m_Canvas.getScale().x / stroke.getScale().x, m_Canvas->m_Canvas.getScale().y / stroke.getScale().y));*/
		stroke.setPosition(m_RenderWindow->getSize().x / 2, m_RenderWindow->getSize().y / 2);
	}
	
}

void CBrush::Undo()
{
	while (PaintedBrushList.size() > 0)
	{
		PaintedBrushList.pop_front();
	}
}
