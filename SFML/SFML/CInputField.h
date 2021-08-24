//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CInputField.h
// Description : CInputField Header file.
// Author : William Inman
// Mail : william.inman@mds.ac.nz
//

#pragma once
#include <SFML/Graphics.hpp>
#include <utils-master/stringutils.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>

class CInputField
{
public:
	std::string m_Label;

	CInputField(sf::RenderWindow* _RenderWindow);
	~CInputField();

	void Update();
	void Render();

	void SetMousePosition(sf::Vector2f Position);
	sf::Vector2f GetMousePosition();

	bool bIsinBounds(sf::Vector2f _vMousePosition);

	void SetLabel(std::string _label);

	void SetState(std::string type);

	void SetPosition(float newX, float newY);

	inline float GetHeight()
	{
		return Sprite.getGlobalBounds().height;
	}

	inline float GetWidth()
	{
		return Sprite.getGlobalBounds().width;
	}

	std::string removeLastChar(std::string s);


private:
	bool m_bIsHovering;
	bool m_bIsPressed;

	sf::RenderWindow* m_RenderWindow;
	sf::Text m_tLabel;
	
	std::string m_OnClickLabel;
	std::string m_HoverLabel;
	sf::Sprite Sprite;

	sf::Texture m_IdleTexture;
	sf::Texture m_HoverTexture;

	sf::Font m_Font;

	sf::Vector2f m_vMousePosition;
};

