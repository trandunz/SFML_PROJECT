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
	m_PreviewStrokeBounds = sf::RectangleShape();
	
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
	sf::Vector2f worldPose = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PreviewStrokeBounds.getPosition()));

	m_RenderWindow->draw(m_PreviewStrokeBounds);
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

			m_PreviewStroke = sf::CircleShape(1);
			m_PreviewStrokeBounds = sf::RectangleShape();
			m_PreviewStroke.setOrigin(m_PreviewStroke.getGlobalBounds().width / 2, m_PreviewStroke.getGlobalBounds().height / 2);
			m_PreviewStroke.setPosition(m_vMouseStart);
			m_PreviewStrokeBounds.setPosition(m_vMouseStart);

			

			m_bCreatePreviewShape = false;
		}

		if (m_ShapeType != LINE)
		{
			float x = (m_vMouseStart.x - m_vMousePosition.x);
			float y = (m_vMouseStart.y - m_vMousePosition.y);

			
			m_PreviewStrokeBounds.setOutlineColor(sf::Color::Transparent);
			m_PreviewStrokeBounds.setFillColor(sf::Color::Transparent);
			/*m_PreviewStrokeBounds.setOrigin(sf::Vector2f(m_vMousePosition.x - m_vMouseStart.x, m_vMousePosition.y - m_vMouseStart.y));
			m_PreviewStrokeBounds.setSize(sf::Vector2f(m_vMousePosition.x - m_vMouseStart.x, m_vMousePosition.y - m_vMouseStart.y));*/
			SetRectangle(m_vMouseStart, m_vMousePosition, m_PreviewStrokeBounds);
			
			
			
			m_PreviewStroke.setFillColor(m_Colour);
			m_PreviewStroke.setPointCount(m_SideCount);
			
			m_PreviewStroke.setRotation(0);
			
			/*m_PreviewStroke.setPosition(m_PreviewStrokeBounds.getPosition().x, m_PreviewStrokeBounds.getPosition().y);*/
			m_PreviewStroke.setScale(m_PreviewStrokeBounds.getSize().x / 4, m_PreviewStrokeBounds.getSize().y / 4);
			m_PreviewStroke.setOutlineThickness(m_OutlineThickness);
			m_PreviewStroke.setOutlineColor(m_OutlineColour);
			m_PreviewStroke.setRotation(m_Rotation);
		}
		else
		{
			m_PreviewLine = sf::VertexArray(sf::Lines, 2);

			m_PreviewLine[0].position = sf::Vector2f(m_vMouseStart.x, m_vMouseStart.y);
			m_PreviewLine[0].color = m_OutlineColour;
			m_PreviewLine[1].position = sf::Vector2f(m_vMousePosition.x, m_vMousePosition.y);
			m_PreviewLine[1].color = m_OutlineColour;
		}
		
		m_ShapeSize = 1;
		Render();

		/*std::cout << m_Stroke->getRadius() << std::endl;*/
	}
}

void CShapes::SetRectangle(sf::Vector2f& startPos, sf::Vector2f& mousePos, sf::RectangleShape& rec)
{
	if (mousePos.x < startPos.x && mousePos.y < startPos.y)//Mouse is left up of start, use mouse for x and y
	{
		rec.setPosition(mousePos.x, mousePos.y);
		rec.setSize(sf::Vector2f(startPos.x - mousePos.x, startPos.y - mousePos.y));
	}
	else if (mousePos.x < startPos.x)//Rectagle is left down of start pos
	{
		rec.setPosition(mousePos.x, startPos.y);
		rec.setSize(sf::Vector2f(startPos.x - mousePos.x, mousePos.y - startPos.y));
	}
	else if (mousePos.y < startPos.y)//Rectagle is right up of start pos
	{
		rec.setPosition(startPos.x, mousePos.y);
		rec.setSize(sf::Vector2f(mousePos.x - startPos.x, startPos.y - mousePos.y));
	}
	else//Rectangle is right down, default state
	{
		rec.setPosition(startPos.x, startPos.y);
		rec.setSize(sf::Vector2f(mousePos.x - startPos.x, mousePos.y - startPos.y));
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
		m_Stroke->setOrigin(m_Stroke->getGlobalBounds().width/2, m_Stroke->getGlobalBounds().height / 2);
		m_Stroke->setPosition(m_vMouseStart);
		m_Stroke->setPointCount(100);
		m_Stroke->setScale(m_PreviewStrokeBounds.getSize().x / 4, m_PreviewStrokeBounds.getSize().y / 4);

		m_Rotation = 0;
		m_Stroke->setRotation(m_Rotation);
		
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
		m_Stroke->setOrigin(m_Stroke->getGlobalBounds().width / 2, m_Stroke->getGlobalBounds().height / 2);
		m_Stroke->setPosition(m_vMouseStart);
		m_Stroke->setPointCount(3);
		m_Stroke->setScale(m_PreviewStrokeBounds.getSize().x / 4, m_PreviewStrokeBounds.getSize().y / 4);

		m_Rotation = 0;
		m_Stroke->setRotation(m_Rotation);
		
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
		m_Stroke->setOrigin(m_Stroke->getGlobalBounds().width / 2, m_Stroke->getGlobalBounds().height / 2);
		m_Stroke->setPosition(m_vMouseStart);
		m_Stroke->setPointCount(4);
		m_Stroke->setScale(m_PreviewStrokeBounds.getSize().x / 4, m_PreviewStrokeBounds.getSize().y / 4);

		m_Rotation = 45;
		m_Stroke->setRotation(m_Rotation);

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
		m_Stroke->setOrigin(m_Stroke->getGlobalBounds().width / 2, m_Stroke->getGlobalBounds().height / 2);
		m_Stroke->setPosition(m_vMouseStart);
		m_Stroke->setPointCount(m_SideCount);
		m_Stroke->setScale(m_PreviewStrokeBounds.getSize().x / 4, m_PreviewStrokeBounds.getSize().y / 4);

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
		m_Stroke->setOrigin(m_Stroke->getGlobalBounds().width / 2, m_Stroke->getGlobalBounds().height / 2);
		m_Stroke->setPosition(m_vMouseStart);
		m_Stroke->setPointCount(100);
		m_Stroke->setScale(m_PreviewStrokeBounds.getSize().x / 4, m_PreviewStrokeBounds.getSize().y / 4);

		m_Rotation = 0;
		m_Stroke->setRotation(m_Rotation);
		
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
