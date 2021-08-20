#include "CShapes.h"

CShapes::CShapes(sf::RenderWindow* _renderWindow, CCanvas* _canvas)
{
	m_Canvas = _canvas;
	m_RenderWindow = _renderWindow;
	m_Rotation = 0;
	m_BushSize = 10;
	m_SideCount = 8;
	m_Stroke = nullptr;
	m_bCreateShape = false;
	
	m_ShapeType = SHAPETYPE::DEFAULT;
}

CShapes::~CShapes()
{
	std::list<sf::CircleShape>::iterator it = PaintedShapeList.begin();
	while (PaintedShapeList.size() > 0)
	{
		PaintedShapeList.erase(it);
		std::advance(it, 1);
		/*PaintedShapeList.pop_front();*/
		/*std::cout << "PopedFront" << std::endl;*/
	}
	m_Stroke = nullptr;
	m_Canvas = nullptr;
	m_RenderWindow = nullptr;
}

void CShapes::Render()
{
	for (const sf::CircleShape& stroke : PaintedShapeList)
	{
		m_RenderWindow->draw(stroke);
		sf::Vector2f worldPosC = m_RenderWindow->mapPixelToCoords(sf::Vector2i(stroke.getPosition()));
	}
}

void CShapes::Update()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((*m_RenderWindow));
	SetMousePosition(m_RenderWindow->mapPixelToCoords(pixelPos));
}

void CShapes::PaintShape()
{
	if (m_Canvas->m_Canvas.getGlobalBounds().contains(sf::Vector2f(m_vMousePosition.x, m_vMousePosition.y)) && !m_bCreateShape)
	{
		m_bCreateShape = true;

		switch (m_ShapeType)
		{
		case CIRCLE:
		{
			m_Stroke = new sf::CircleShape(m_BushSize);
			m_Stroke->setOrigin(m_Stroke->getGlobalBounds().width / 2, m_Stroke->getGlobalBounds().height / 2);
			m_Stroke->setFillColor(m_Colour);
			m_Stroke->setPosition(m_vMousePosition);
			m_Rotation = 0;
			m_Stroke->rotate(m_Rotation);
			PaintedShapeList.push_back(*m_Stroke);
			m_Stroke = nullptr;
		}
		case TRIANGLE:
		{
			m_Stroke = new sf::CircleShape(m_BushSize, 3);
			m_Stroke->setOrigin(m_Stroke->getGlobalBounds().width / 2, m_Stroke->getGlobalBounds().height / 2);
			m_Stroke->setFillColor(m_Colour);
			m_Stroke->setPosition(m_vMousePosition);
			m_Rotation = 0;
			m_Stroke->rotate(m_Rotation);
			PaintedShapeList.push_back(*m_Stroke);
			m_Stroke = nullptr;
		}
		case SQUARE:
		{
			m_Stroke = new sf::CircleShape (m_BushSize, 4);
			m_Stroke->setOrigin(m_Stroke->getGlobalBounds().width / 2, m_Stroke->getGlobalBounds().height / 2);
			m_Stroke->setFillColor(m_Colour);
			m_Stroke->setPosition(m_vMousePosition);
			m_Rotation = 45;
			m_Stroke->rotate(m_Rotation);
			PaintedShapeList.push_back(*m_Stroke);
			m_Stroke = nullptr;
			break;
		}
		case CUSTOM:
		{
			m_Stroke = new sf::CircleShape(m_BushSize, m_SideCount);
			m_Stroke->setOrigin(m_Stroke->getGlobalBounds().width / 2, m_Stroke->getGlobalBounds().height / 2);
			m_Stroke->setFillColor(m_Colour);
			m_Stroke->setPosition(m_vMousePosition);
			m_Rotation = 0;
			m_Stroke->rotate(m_Rotation);
			PaintedShapeList.push_back(*m_Stroke);
			m_Stroke = nullptr;
		}
		case SPRITE:
		{
			break;
		}
		default:
		{
			m_Stroke = new sf::CircleShape(m_BushSize);
			m_Stroke->setOrigin(m_Stroke->getGlobalBounds().width / 2, m_Stroke->getGlobalBounds().height / 2);
			m_Stroke->setFillColor(m_Colour);
			m_Stroke->setPosition(m_vMousePosition);
			m_Rotation = 0;
			m_Stroke->rotate(m_Rotation);
			PaintedShapeList.push_back(*m_Stroke);
			m_Stroke = nullptr;

			if (m_bCreateShape)
			{

			}
			break;
		}
		}
		
	}
	
		





		std::cout << m_vMousePosition.x << std::endl;
		std::cout << m_vMousePosition.y << std::endl;

}

void CShapes::SetMousePosition(sf::Vector2f Position)
{
	m_vMousePosition = Position;
}

sf::Vector2f CShapes::GetMousePosition()
{
	return m_vMousePosition;
}

void CShapes::SetActiveColour(sf::Color _Color)
{
	m_Colour = _Color;
}

void CShapes::Undo()
{
	std::list<sf::CircleShape>::iterator it = PaintedShapeList.begin();
	while (PaintedShapeList.size() > 0)
	{
		PaintedShapeList.erase(it);
		std::advance(it, 1);
		/*PaintedShapeList.pop_front();*/
		/*std::cout << "PopedFront" << std::endl;*/
	}
}
