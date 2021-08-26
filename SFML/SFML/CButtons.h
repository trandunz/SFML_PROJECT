//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CButtons.h
// Description : CButtons Header file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#pragma once

// Non-Local Includes
#include <SFML/Graphics.hpp>

class CButtons
{
public:
	enum STATE
	{
		Idle,
		Hover,
		Click,
	};

	bool m_bIsHovering;
	bool m_bIsPressed;
	bool m_bIsClicked;

	std::string m_Label;
	std::string m_OnClickLabel;
	std::string m_HoverLabel;

	sf::Sprite Sprite;

	sf::Text m_tLabel;

	CButtons(sf::RenderWindow* _renderWindow);
	~CButtons();

	void Start();
	void Update();
	void Render();

	void RenderOnlyLabel();

	void SetMousePosition(sf::Vector2f _position);
	sf::Vector2f GetMousePosition();

	void SetPosition(float _newX, float _newY);

	void SetLabel(std::string x);

	 
	void SetState(std::string type);

	bool bIsinBounds(sf::Vector2f _vMousePosition);

	void SetHoverTex(sf::Texture _newTexture);
	void SetIdleTex(sf::Texture _newTexture);
	void SetClickTex(sf::Texture _newTexture);

	inline sf::Texture GetHoverText()
	{
		return m_HoverTexture;
	}
	inline sf::Texture GetClickText()
	{
		return m_ClickTexture;
	}

	int GetHeight();
	int GetWidth();

private:
	sf::RenderWindow* m_RenderWindow;

	sf::Texture m_IdleTexture;
	sf::Texture m_HoverTexture;
	sf::Texture m_ClickTexture;

	sf::Font m_Font;

	sf::Vector2f m_vMousePosition;
};

