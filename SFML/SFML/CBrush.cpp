//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CBrush.cpp
// Description : CBrush Implementation file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

// Local Includes
#include "CBrush.h"

/// <summary>
/// Paint Brush Constructor.
/// Takes in:	sf::RenderWindow* (Intended To Be The Main Render Window With Canvas e.t.c) and CCanvas*
/// </summary>
CBrush::CBrush(sf::RenderWindow* _renderWindow, CCanvas* _canvas)
{
	// Initilization
	m_Canvas = _canvas;
	m_RenderWindow = _renderWindow;

	m_Rotation = 0;
	m_BushSize = 1;
	m_SideCount = 8;

	m_BrushType = BRUSHTYPE::DEFAULT;
}

/// <summary>
/// Paint Brush Destructor.
/// </summary>
CBrush::~CBrush()
{
	while (PaintedBrushList.size() > 0)
	{
		PaintedBrushList.pop_front();

		/*std::cout << "PopedFront" << std::endl;*/
	}
	while (PaintedImageList.size() > 0)
	{
		PaintedImageList.pop_front();

		/*std::cout << "PopedFront" << std::endl;*/
	}

	m_Canvas = nullptr;
	m_RenderWindow = nullptr;
}

/// <summary>
/// Render Definition For Paint Brush.
/// </summary>
void CBrush::Render()
{
	// Image Stamp Stokes
	for (const sf::Sprite& stroke : PaintedImageList)
	{
		m_RenderWindow->draw(stroke);

		sf::Vector2f worldPosC = m_RenderWindow->mapPixelToCoords(sf::Vector2i(stroke.getPosition()));
	}
	// Paint Brush Stokes
	for (const sf::CircleShape& stroke : PaintedBrushList)
	{
		m_RenderWindow->draw(stroke);

		sf::Vector2f worldPosC = m_RenderWindow->mapPixelToCoords(sf::Vector2i(stroke.getPosition()));
	}
}

/// <summary>
/// Update For Paint Brush.
/// </summary>
void CBrush::Update()
{
	// Set m_vMousePosition To Mouse Position
	sf::Vector2i pixelPos = sf::Mouse::getPosition((*m_RenderWindow));

	SetMousePosition(m_RenderWindow->mapPixelToCoords(pixelPos));
}

/// <summary>
/// Creates A New Shape With Radius (m_BrushSize) And Places At Mouse Position
/// </summary>
void CBrush::PaintBrush()
{
	// Mouse Is In Canvas
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
			stroke.setRotation(m_Rotation);

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
			stroke.setRotation(m_Rotation);

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
			stroke.setRotation(m_Rotation);

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
			stroke.setRotation(m_Rotation);

			PaintedBrushList.push_back(stroke);

			break;
		}
		case SPRITE:
		{
			m_ImageBrushTexture.loadFromFile("Images/ShapeIcon.png");
			sf::Sprite stroke;
			stroke.setTexture(m_ImageBrushTexture, 1);
			stroke.setOrigin(stroke.getGlobalBounds().width / 2, stroke.getGlobalBounds().height / 2);
			stroke.setPosition(m_vMousePosition);

			m_Rotation = 0;
			stroke.setRotation(m_Rotation);

			PaintedImageList.push_back(stroke);

			break;
		}	
		default:
		{
			sf::CircleShape stroke(m_BushSize);

			stroke.setOrigin(stroke.getGlobalBounds().width / 2, stroke.getGlobalBounds().height / 2);
			stroke.setFillColor(m_Colour);
			stroke.setPosition(m_vMousePosition);

			m_Rotation = 0;
			stroke.setRotation(m_Rotation);

			PaintedBrushList.push_back(stroke);

			break;
		}
		}

		/*std::cout << stroke.getPosition().x << std::endl;
		std::cout << stroke.getPosition().y << std::endl;*/
	}
}

/// <summary>
/// Sets The Mouse Position Specified Parameter
/// Takes In: sf::Vector2f (_position)
/// </summary>
/// <param name="Position"></param>
void CBrush::SetMousePosition(sf::Vector2f _position)
{
	m_vMousePosition = _position;
}

/// <summary>
/// Returns The Mouse Position (sf::Vector2f)
/// </summary>
/// <returns></returns>
sf::Vector2f CBrush::GetMousePosition()
{
	/*std::cout << m_vMousePosition.x << std::endl;
	std::cout << m_vMousePosition.y << std::endl;*/

	return m_vMousePosition;
}

/// <summary>
/// Sets The Active Color to Secified Parameter
/// Takes In: sf::Color (Color)
/// </summary>
/// <param name="_Color"></param>
void CBrush::SetActiveColour(sf::Color _color)
{
	m_Colour = _color;
}

/// <summary>
/// Undo The Previous Paint Brush Stroke.
/// </summary>
void CBrush::Undo()
{
	if (PaintedBrushList.size() > 0)
	{
		PaintedBrushList.pop_back();
	}
	if (PaintedImageList.size() > 0)
	{
		PaintedImageList.pop_back();
	}
}