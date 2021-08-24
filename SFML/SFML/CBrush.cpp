#include "CBrush.h"

CBrush::CBrush(sf::RenderWindow* _renderWindow, CCanvas* _canvas)
{
	m_Canvas = _canvas;
	m_RenderWindow = _renderWindow;
	m_Rotation = 0;
	m_BushSize = 1;
	m_SideCount = 8;
	m_BrushType = BRUSHTYPE::DEFAULT;
}

CBrush::~CBrush()
{
	while (PaintedBrushList.size() > 0)
	{
		PaintedBrushList.pop_front();
		/*std::cout << "PopedFront" << std::endl;*/
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
	sf::Vector2i pixelPos = sf::Mouse::getPosition((*m_RenderWindow));
	SetMousePosition(m_RenderWindow->mapPixelToCoords(pixelPos));
}

void CBrush::PaintBrush()
{
	if (m_Canvas->m_Canvas.getGlobalBounds().contains(sf::Vector2f(m_vMousePosition.x, m_vMousePosition.y)))
	{
		switch (m_BrushType)
		{
		case CIRCLE:
		{
			sf::CircleShape stroke(m_BushSize);
			stroke.setOrigin(stroke.getGlobalBounds().width / 2, stroke.getGlobalBounds().height / 2);
			stroke.setFillColor(m_Colour);
			stroke.setPosition(m_vMousePosition);
			m_Rotation = 0;
			stroke.rotate(m_Rotation);
			PaintedBrushList.push_back(stroke);
			break;
		}
		case TRIANGLE:
		{
			sf::CircleShape stroke(m_BushSize, 3);
			stroke.setOrigin(stroke.getGlobalBounds().width / 2, stroke.getGlobalBounds().height / 2);
			stroke.setFillColor(m_Colour);
			stroke.setPosition(m_vMousePosition);
			m_Rotation = 0;
			stroke.rotate(m_Rotation);
			PaintedBrushList.push_back(stroke);
			break;
		}
		case SQUARE:
		{
			sf::CircleShape stroke(m_BushSize, 4);
			stroke.setOrigin(stroke.getGlobalBounds().width / 2, stroke.getGlobalBounds().height / 2);
			stroke.setFillColor(m_Colour);
			stroke.setPosition(m_vMousePosition);
			m_Rotation = 45;
			stroke.rotate(m_Rotation);
			PaintedBrushList.push_back(stroke);
			break;
		}
		case CUSTOM:
		{
			sf::CircleShape stroke(m_BushSize, m_SideCount);
			stroke.setOrigin(stroke.getGlobalBounds().width / 2, stroke.getGlobalBounds().height / 2);
			stroke.setFillColor(m_Colour);
			stroke.setPosition(m_vMousePosition);
			m_Rotation = 0;
			stroke.rotate(m_Rotation);
			PaintedBrushList.push_back(stroke);
			break;
		}
		case SPRITE:
		{
			break;
		}	
		default:
		{
			sf::CircleShape stroke(m_BushSize);
			stroke.setOrigin(stroke.getGlobalBounds().width / 2, stroke.getGlobalBounds().height / 2);
			stroke.setFillColor(m_Colour);
			stroke.setPosition(m_vMousePosition);
			m_Rotation = 0;
			stroke.rotate(m_Rotation);
			PaintedBrushList.push_back(stroke);
			break;
		}
		}

		
		

		
		/*std::cout << stroke.getPosition().x << std::endl;
		std::cout << stroke.getPosition().y << std::endl;*/
		
	}
}

void CBrush::SetMousePosition(sf::Vector2f Position)
{
	m_vMousePosition = Position;
}

sf::Vector2f CBrush::GetMousePosition()
{
	/*std::cout << m_vMousePosition.x << std::endl;
	std::cout << m_vMousePosition.y << std::endl;*/

	return m_vMousePosition;
}

void CBrush::SetActiveColour(sf::Color _Color)
{
	m_Colour = _Color;
}

void CBrush::Undo()
{
	if (PaintedBrushList.size() > 0)
	{
		PaintedBrushList.pop_back();
	}
	
}

//sf::Color CBrush::setPixelColor(int x, int y, sf::Color color)
//{
//	{
//		// Set pixel to color
//		m_Canvas->m_CanvasImage->setPixel(x, y, color);
//
//		return color;
//	}
//}
