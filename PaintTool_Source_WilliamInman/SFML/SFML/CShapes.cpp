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

// Local Includes
#include "CShapes.h"

/// <summary>
/// Shape Brush Constructor.
/// Takes in:	sf::RenderWindow* (Intended To Be The Main Render Window With Canvas e.t.c) and CCanvas*
/// </summary>
CShapes::CShapes(sf::RenderWindow* _renderWindow, CCanvas* _canvas)
{
	// Initilization
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

/// <summary>
/// Shape Brush Destructor.
/// </summary>
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

/// <summary>
/// Render Definition For Shapes.
/// </summary>
void CShapes::Render()
{
	// Shapes
	for (sf::CircleShape& stroke : PaintedShapeList)
	{
		m_RenderWindow->draw(stroke);
		sf::Vector2f worldPosC = m_RenderWindow->mapPixelToCoords(sf::Vector2i(stroke.getPosition()));
	}
	// Lines
	for (sf::VertexArray& line : PaintedLineList)
	{
		m_RenderWindow->draw(line);
		sf::Vector2f worldPosD = m_RenderWindow->mapPixelToCoords(sf::Vector2i(line[0].position));
		sf::Vector2f worldPosE = m_RenderWindow->mapPixelToCoords(sf::Vector2i(line[1].position));
	}
	
	// Map Line Vertex To Coords
	if (m_PreviewLine.getVertexCount() != 0)
	{
		sf::Vector2f worldPosVo = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PreviewLine[0].position));
		sf::Vector2f worldPosVt = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PreviewLine[1].position));
	}

	// Map Preview Strokes Position To Coords
	sf::Vector2f worldPosd = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PreviewStroke.getPosition()));
	sf::Vector2f worldPose = m_RenderWindow->mapPixelToCoords(sf::Vector2i(m_PreviewStrokeBounds.getPosition()));

	// Draw
	m_RenderWindow->draw(m_PreviewStrokeBounds);
	m_RenderWindow->draw(m_PreviewStroke);
	m_RenderWindow->draw(m_PreviewLine);
}

/// <summary>
/// Update For Shapes Brush.
/// </summary>
void CShapes::Update()
{
	// Set m_vMousePosition To Mouse Position
	sf::Vector2i pixelPos = sf::Mouse::getPosition((*m_RenderWindow));

	SetMousePosition(m_RenderWindow->mapPixelToCoords(pixelPos));

	/*std::cout << m_vMousePosition.x << "  " << m_vMousePosition.y << std::endl;*/
}

/// <summary>
/// Creates A Preview Stoke For The Specified Shape Type
/// </summary>
void CShapes::PaintShape()
{
	// Mouse Is In Canvas
	if (m_Canvas->m_Canvas.getGlobalBounds().contains(sf::Vector2f(m_vMousePosition.x, m_vMousePosition.y)) )
	{
		// Create Preview Shape Check
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
		// Shape Other Than Line
		if (m_ShapeType != LINE)
		{
			// Make PreviewStroke Bounds Shape Transparent
			m_PreviewStrokeBounds.setOutlineColor(sf::Color::Transparent);
			m_PreviewStrokeBounds.setFillColor(sf::Color::Transparent);

			// Set Size Of PreviewStroke Bounds Shape
			SetRectangle(m_vMouseStart, m_vMousePosition, m_PreviewStrokeBounds);
			
			// Preview Stroke
			m_PreviewStroke.setFillColor(m_Colour);
			m_PreviewStroke.setPointCount(m_SideCount);

			m_PreviewStroke.setRotation(0);
			m_PreviewStroke.setScale(m_PreviewStrokeBounds.getSize().x / 4, m_PreviewStrokeBounds.getSize().y / 4);
			m_PreviewStroke.setOutlineThickness(m_OutlineThickness);
			m_PreviewStroke.setOutlineColor(m_OutlineColour);
			m_PreviewStroke.setRotation(m_Rotation);
		}
		// Shape Is Line
		else
		{
			m_PreviewLine = sf::VertexArray(sf::Lines, 2);

			// Vert 1
			m_PreviewLine[0].position = sf::Vector2f(m_vMouseStart.x, m_vMouseStart.y);
			m_PreviewLine[0].color = m_OutlineColour;

			// Vert 2
			m_PreviewLine[1].position = sf::Vector2f(m_vMousePosition.x, m_vMousePosition.y);
			m_PreviewLine[1].color = m_OutlineColour;
		}
		
		m_ShapeSize = 1;

		Render();

		/*std::cout << m_Stroke->getRadius() << std::endl;*/
	}
}

/// <summary>
/// Sets The sf::RectangleShape (rec) To The Difference Between startPos and mousePos
/// Takes In: sf::Vector2f Adress (Start Position), sf::Vector2f Adress (Mouse Position), sf::RectangleShape Adress (Rectangle To Set)
/// </summary>
/// <param name="startPos"></param>
/// <param name="mousePos"></param>
/// <param name="rec"></param>
void CShapes::SetRectangle(sf::Vector2f& _startPos, sf::Vector2f& _mousePos, sf::RectangleShape& _rec)
{
	// Mouse Is Left Up Of Start
	if (_mousePos.x < _startPos.x && _mousePos.y < _startPos.y)
	{
		_rec.setPosition(_mousePos.x, _mousePos.y);
		_rec.setSize(sf::Vector2f(_startPos.x - _mousePos.x, _startPos.y - _mousePos.y));
	}
	// Mouse Is Left Down Of Start
	else if (_mousePos.x < _startPos.x)
	{
		_rec.setPosition(_mousePos.x, _startPos.y);
		_rec.setSize(sf::Vector2f(_startPos.x - _mousePos.x, _mousePos.y - _startPos.y));
	}
	// Mouse Is Right Up Of Start
	else if (_mousePos.y < _startPos.y)
	{
		_rec.setPosition(_startPos.x, _mousePos.y);
		_rec.setSize(sf::Vector2f(_mousePos.x - _startPos.x, _startPos.y - _mousePos.y));
	}
	// Mouse Is Right Down Of Start
	else
	{
		_rec.setPosition(_startPos.x, _startPos.y);
		_rec.setSize(sf::Vector2f(_mousePos.x - _startPos.x, _mousePos.y - _startPos.y));
	}
}

/// <summary>
/// Creates A Shape For The Specified Shape Type That Scales To Fit The Preview Shape
/// </summary>
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

	// Cleanup
	m_bCreateShape = false;
	m_Stroke = nullptr;

	m_PreviewStroke = sf::CircleShape();
	m_PreviewLine = sf::VertexArray();

	// Render & Update
	Render();
	Update();

	// Debug
	std::cout << "  Let Go" << std::endl;
}

/// <summary>
/// Sets The Mouse Position Specified Parameter
/// Takes In: sf::Vector2f (Position)
/// </summary>
/// <param name="Position"></param>
void CShapes::SetMousePosition(sf::Vector2f _position)
{
	m_vMousePosition = _position;
}

/// <summary>
/// Returns The Mouse Position (sf::Vector2f)
/// </summary>
/// <returns></returns>
sf::Vector2f CShapes::GetMousePosition()
{
	return m_vMousePosition;
}

/// <summary>
/// Sets The Active Color to Secified Parameter
/// Takes In: sf::Color (Color)
/// </summary>
/// <param name="_Color"></param>
void CShapes::SetActiveColour(sf::Color _color)
{
	m_Colour = _color;
}

/// <summary>
/// Undo The Previous Shape Drawn
/// </summary>
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
