//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CShapes.cpp
// Description : CShapes Implementation file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#include "CShapes.h"

CShapes::CShapes(sf::RenderWindow* _renderWindow, CCanvas* _canvas)
{
	m_Canvas = _canvas;
	m_RenderWindow = _renderWindow;

	m_Rotation = 0;
	m_SideCount = 8;
	m_ShapeSize = 0;

	m_Stroke = nullptr;
	m_bCreateShape = false;

	m_PreviewStroke = sf::CircleShape();
	m_PreviewLine = sf::VertexArray();
	
	m_ShapeType = SHAPETYPE::DEFAULT;
}

CShapes::~CShapes()
{
	std::list<sf::CircleShape>::iterator ShapeIter = PaintedShapeList.begin();
	while (PaintedShapeList.size() > 0)
	{
		PaintedShapeList.erase(ShapeIter);
		std::advance(ShapeIter, 1);
		/*PaintedShapeList.pop_front();*/
		/*std::cout << "PopedFront" << std::endl;*/
	}

	while (PaintedShapeList.size() > 0)
	{
		PaintedLineList.pop_front();

	}

	m_Stroke = nullptr;
	m_Canvas = nullptr;
	m_RenderWindow = nullptr;
}

void CShapes::Render()
{
	for (sf::CircleShape& stroke : PaintedShapeList)
	{
		m_RenderWindow->draw(stroke);
		sf::Vector2f worldPosC = m_RenderWindow->mapPixelToCoords(sf::Vector2i(stroke.getPosition()));
	}

	for (sf::VertexArray& line : PaintedLineList)
	{
		m_RenderWindow->draw(line);
		sf::Vector2f worldPosD = m_RenderWindow->mapPixelToCoords(sf::Vector2i(line[0].position));
		sf::Vector2f worldPosE = m_RenderWindow->mapPixelToCoords(sf::Vector2i(line[1].position));
	}
	
	if (m_PreviewLine.getVertexCount() != 0)
	{
		sf::Vector2f worldPosVo = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PreviewLine[0].position));
		sf::Vector2f worldPosVt = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PreviewLine[1].position));
	}

	sf::Vector2f worldPosd = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PreviewStroke.getPosition()));

	m_RenderWindow->draw(m_PreviewStroke);
	m_RenderWindow->draw(m_PreviewLine);
}

void CShapes::Update()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((*m_RenderWindow));

	SetMousePosition(m_RenderWindow->mapPixelToCoords(pixelPos));

	/*std::cout << m_vMousePosition.x << "  " << m_vMousePosition.y << std::endl;*/
}

void CShapes::PaintShape()
{
	if (m_Canvas->m_Canvas.getGlobalBounds().contains(sf::Vector2f(m_vMousePosition.x, m_vMousePosition.y)) )
	{
		if (m_bCreatePreviewShape)
		{
			m_vMouseStart = m_vMousePosition;

			m_PreviewStroke = sf::CircleShape();
			m_PreviewStroke.setPosition(m_vMouseStart);

			m_bCreatePreviewShape = false;
		}

		if (m_ShapeType != LINE)
		{
			float x = (m_vMousePosition.x - m_vMouseStart.x);
			float y = (m_vMouseStart.y - m_vMousePosition.y) * (m_vMouseStart.y - m_vMousePosition.y);

			m_ShapeSize = x;

			m_PreviewStroke.setFillColor(m_Colour);
			m_PreviewStroke.setPointCount(m_SideCount);
			m_PreviewStroke.setRotation(m_Rotation);
			m_PreviewStroke.setRadius(m_ShapeSize);
			m_PreviewStroke.setOutlineThickness(m_OutlineThickness);
			m_PreviewStroke.setOutlineColor(m_OutlineColour);
		}
		else
		{
			m_PreviewLine = sf::VertexArray(sf::Lines, 2);

			m_PreviewLine[0].position = sf::Vector2f(m_vMouseStart.x, m_vMouseStart.y);
			m_PreviewLine[0].color = m_OutlineColour;
			m_PreviewLine[1].position = sf::Vector2f(m_vMousePosition.x, m_vMousePosition.y);
			m_PreviewLine[1].color = m_OutlineColour;
		}
		
		Render();

		/*std::cout << m_Stroke->getRadius() << std::endl;*/
	}
}

void CShapes::LetGoOfShape()
{
	switch (m_ShapeType)
	{
	case LINE:
	{
		sf::VertexArray line(sf::Lines, 2);

		line[0].position = sf::Vector2f(m_vMouseStart.x, m_vMouseStart.y);
		line[0].color = m_OutlineColour;

		line [1].position = sf::Vector2f(m_PreviewLine[1].position.x, m_PreviewLine[1].position.y);
		line[1].color = m_OutlineColour;
		
		PaintedLineList.push_back(line);
		break;
	}
	case CIRCLE:
	{
		m_Stroke = nullptr;
		m_Stroke = new sf::CircleShape(m_ShapeSize);

		m_Stroke->setFillColor(m_Colour);
		m_Stroke->setPosition(m_PreviewStroke.getPosition());

		m_Rotation = 0;

		m_Stroke->setRotation(m_Rotation);
		m_Stroke->setPointCount(100);
		m_Stroke->setOutlineThickness(m_OutlineThickness);
		m_Stroke->setOutlineColor(m_OutlineColour);
		PaintedShapeList.push_back(*m_Stroke);
		break;
	}
	case TRIANGLE:
	{
		m_Stroke = nullptr;
		m_Stroke = new sf::CircleShape(m_ShapeSize, 3);

		m_Stroke->setFillColor(m_Colour);
		m_Stroke->setPosition(m_PreviewStroke.getPosition());

		m_Rotation = 0;

		m_Stroke->setRotation(m_Rotation);
		m_Stroke->setPointCount(3);
		m_Stroke->setOutlineThickness(m_OutlineThickness);
		m_Stroke->setOutlineColor(m_OutlineColour);
		PaintedShapeList.push_back(*m_Stroke);
		break;
	}
	case SQUARE:
	{
		m_Stroke = nullptr;
		m_Stroke = new sf::CircleShape(m_ShapeSize, 4);

		m_Stroke->setFillColor(m_Colour);
		m_Stroke->setPosition(m_PreviewStroke.getPosition());
		m_Stroke->setPointCount(4);

		m_Rotation = 45;

		m_Stroke->rotate(m_Rotation);
		m_Stroke->setOutlineThickness(m_OutlineThickness);
		m_Stroke->setOutlineColor(m_OutlineColour);
		PaintedShapeList.push_back(*m_Stroke);
		break;
	}
	case CUSTOM:
	{
		m_Stroke = nullptr;
		m_Stroke = new sf::CircleShape(m_ShapeSize, m_SideCount);

		m_Stroke->setFillColor(m_Colour);
		m_Stroke->setPosition(m_PreviewStroke.getPosition());
		m_Stroke->setPointCount(m_SideCount);

		m_Rotation = 0;

		m_Stroke->setRotation(m_Rotation);
		m_Stroke->setOutlineThickness(m_OutlineThickness);
		m_Stroke->setOutlineColor(m_OutlineColour);
		PaintedShapeList.push_back(*m_Stroke);
		break;
	}
	case SPRITE:
	{
		break;
	}
	default:
	{
		m_Stroke = nullptr;
		m_Stroke = new sf::CircleShape(m_ShapeSize);

		m_Stroke->setFillColor(m_Colour);
		m_Stroke->setPosition(m_PreviewStroke.getPosition());

		m_Rotation = 0;

		m_Stroke->setRotation(m_Rotation);
		m_Stroke->setPointCount(100);
		m_Stroke->setOutlineThickness(m_OutlineThickness);
		m_Stroke->setOutlineColor(m_OutlineColour);
		PaintedShapeList.push_back(*m_Stroke);
		break;
	}
	}

	m_bCreateShape = false;
	m_Stroke = nullptr;

	m_PreviewStroke = sf::CircleShape();
	m_PreviewLine = sf::VertexArray();

	Render();
	Update();

	std::cout << "  Let Go" << std::endl;
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
	if (PaintedShapeList.size() > 0)
	{
		std::list<sf::CircleShape>::iterator it = PaintedShapeList.end();
		it--;
		PaintedShapeList.erase(it);

	}
	if (PaintedLineList.size() > 0)
	{
		std::list<sf::VertexArray>::iterator it = PaintedLineList.end();
		it--;
		PaintedLineList.erase(it);
	}
}
