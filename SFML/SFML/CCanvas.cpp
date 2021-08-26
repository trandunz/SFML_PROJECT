//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CCanvas.cpp
// Description : CCanvas Implementation file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

// Local Includes
#include "CCanvas.h"

/// <summary>
/// Canvas Constructor.
/// </summary>
CCanvas::CCanvas()
{
	// Initilization
	m_RenderWindow = nullptr;
}

/// <summary>
/// Canvas Constructor.
/// Takes in:	sf::RenderWindow* (Intended To Be The Main Render Window With Canvas e.t.c), sf::Vector2f (Size Of Canvas)
/// </summary>
CCanvas::CCanvas(sf::RenderWindow* _renderWindow, sf::Vector2f _size)
{
	// Initilization
	m_RenderWindow = _renderWindow;
	m_Size = _size;

	// BackGround Image
	m_BGTexture.loadFromFile("Images/Background.jpg");
	m_BackGround.setTexture(m_BGTexture);
	m_BackGround.setOrigin(m_BackGround.getGlobalBounds().width / 2, m_BackGround.getGlobalBounds().height / 2);
	m_BackGround.setScale(_size.x / m_BackGround.getScale().x, _size.y / m_BackGround.getScale().y);
	m_BackGround.setPosition(0.0f, 0.0f);

	// Canvas
	m_Canvas = sf::RectangleShape(_size);
	m_Canvas.setOrigin(m_Canvas.getGlobalBounds().width / 2, m_Canvas.getGlobalBounds().height / 2);
	m_Canvas.setPosition(0.0f, 0.0f);
	m_Canvas.setFillColor(m_Color);
}

/// <summary>
/// Canvas Destructor.
/// </summary>
CCanvas::~CCanvas()
{
	// Cleanup Pointer
	m_RenderWindow = nullptr;
}

/// <summary>
/// Assign _window* to m_RenderWindow*
/// Takes In: sf::RenderWindow*
/// </summary>
void CCanvas::SetRenderWindow(sf::RenderWindow* _renderWindow)
{
	m_RenderWindow = _renderWindow;
}

/// <summary>
/// Returns sf::RenderWindow* (m_RenderWindow)
/// </summary>
/// <returns></returns>
sf::RenderWindow* CCanvas::GetRenderWindow()
{
	return m_RenderWindow;
}

/// <summary>
/// Start Function For Canvas (Intended To Be Called Before Update).
/// </summary>
void CCanvas::Start()
{
}

/// <summary>
/// Update Definition For Canvas.
/// </summary>
void CCanvas::Update()
{
	/*std::cout << m_Canvas.getPosition().x << std::endl;
	std::cout << m_Canvas.getPosition().y << std::endl;*/
}

/// <summary>
/// Render Definition For Canvas.
/// </summary>
void CCanvas::Render()
{
	m_RenderWindow->draw(m_BackGround);
	m_RenderWindow->draw(m_Canvas);
}
