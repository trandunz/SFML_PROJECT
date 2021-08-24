//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CButtons.cpp
// Description : CButtons Implementation file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#include "CButtons.h"

CButtons::CButtons(sf::RenderWindow* _RenderWindow)
{
	m_RenderWindow = _RenderWindow;

	m_IdleTexture.loadFromFile("Images/ButtonIdle.png");
	m_HoverTexture.loadFromFile("Images/ButtonHovering.png");
	m_ClickTexture.loadFromFile("Images/ButtonClick.png");
	m_Font.loadFromFile("Fonts/times.TTF");

	m_IdleTexture.setSmooth(true);
	m_HoverTexture.setSmooth(true);
	m_ClickTexture.setSmooth(true);

	m_tLabel.setFont(m_Font);
	m_tLabel.setCharacterSize(24);
	m_tLabel.setFillColor(sf::Color::Black);
	
	Sprite.setTexture(m_IdleTexture, 1);
	
	m_tLabel.setOrigin(sf::Vector2f(m_tLabel.getGlobalBounds().width / 2, m_tLabel.getGlobalBounds().height / 2));
	Sprite.setOrigin(sf::Vector2f(Sprite.getGlobalBounds().width / 2, Sprite.getGlobalBounds().height / 2));

	SetLabel(m_Label);
	
	m_bIsHovering = false;
	m_bIsPressed = false;
	m_bIsClicked = false;

	m_Label = "Default";
	m_OnClickLabel = m_Label;
	m_HoverLabel = m_Label;
}

CButtons::~CButtons()
{
	m_RenderWindow = nullptr;
}

void CButtons::Start()
{
}

void CButtons::Update()
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition((*m_RenderWindow));

	SetMousePosition(m_RenderWindow->mapPixelToCoords(pixelPos));

	bIsinBounds(m_vMousePosition);
}

void CButtons::Render()
{
	m_RenderWindow->draw(Sprite);
	m_RenderWindow->draw(m_tLabel);
}

void CButtons::RenderOnlyLabel()
{
	m_RenderWindow->draw(m_tLabel);
}

void CButtons::SetMousePosition(sf::Vector2f Position)
{
	m_vMousePosition = Position;
}

sf::Vector2f CButtons::GetMousePosition()
{
	/*std::cout << m_vMousePosition.x << std::endl;
	std::cout << m_vMousePosition.y << std::endl;*/

	return m_vMousePosition;
}

void CButtons::SetPosition(float newX, float newY)
{
	Sprite.setPosition(sf::Vector2f(newX, newY));
	m_tLabel.setPosition(sf::Vector2f(newX, newY));
}

void CButtons::SetLabel(std::string _newLabel)
{
	std::string oldLabel = m_Label;
	std::string oldClickLabel = m_OnClickLabel;

	if (_newLabel != m_OnClickLabel && _newLabel != m_HoverLabel)
	{
		m_Label = _newLabel;
	}
	if (m_OnClickLabel == oldLabel && _newLabel != m_HoverLabel)
	{
		m_OnClickLabel = _newLabel;
	}
	if (m_HoverLabel == oldLabel && _newLabel != oldClickLabel)
	{
		m_HoverLabel = _newLabel;
	}

	m_tLabel.setString(_newLabel);
	m_tLabel.setCharacterSize(20);

	m_tLabel.setOrigin(sf::Vector2f(m_tLabel.getGlobalBounds().width / 2, m_tLabel.getGlobalBounds().height / 2));
}

void CButtons::SetState(std::string type)
{
	if (type == "Idle") 
	{
		Sprite.setTexture(m_IdleTexture, 1);
	}
	else if (type == "Hover")
	{
		Sprite.setTexture(m_HoverTexture, 1);
	}
	else if (type == "Click")
	{
		Sprite.setTexture(m_ClickTexture, 1);
	}
}

bool CButtons::bIsinBounds(sf::Vector2f _vMousePosition)
{
	if (Sprite.getGlobalBounds().contains(sf::Vector2f(_vMousePosition.x, _vMousePosition.y)))
	{
		m_bIsHovering = true;

		if (m_bIsPressed == false) 
		{
			Sprite.setTexture(m_HoverTexture, 1);

			SetLabel(m_HoverLabel);

			SetState("Hover");
		}
		if (m_bIsPressed == true)
		{
			Sprite.setTexture(m_ClickTexture, 1);

			SetLabel(m_Label);

			SetState("Click");
		}

		/*std::cout << "MousedOverButton" << std::endl;*/

		return true;
	}
	else
	{
		m_bIsHovering = false;

		if (m_bIsPressed) 
		{
			SetLabel(m_Label);

			SetState("Click");
		}
		else if (!m_bIsPressed)
		{
			Sprite.setTexture(m_IdleTexture, 1);

			SetLabel(m_Label);

			SetState("Idle");
		}
		
		return false;
	}
}

void CButtons::SetHoverTex(sf::Texture _newTexture)
{
	m_HoverTexture = _newTexture;
}

void CButtons::SetIdleTex(sf::Texture _newTexture)
{
	m_IdleTexture = _newTexture;
}

void CButtons::SetClickTex(sf::Texture _newTexture)
{
	m_ClickTexture = _newTexture;
}

int CButtons::GetHeight()
{
	return Sprite.getGlobalBounds().height;
}

int CButtons::GetWidth()
{
	return Sprite.getGlobalBounds().width;
}