#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class CButtons
{
public:
	bool m_bIsHovering;
	bool m_bIsPressed;
	bool m_bIsClicked;
	string m_Label;
	string m_OnClickLabel;
	string m_HoverLabel;
	sf::Sprite Sprite;
	sf::Text m_tLabel;

	CButtons(sf::RenderWindow* _RenderWindow);
	~CButtons();

	void Start();
	void Update();
	void Render();

	void SetPosition(float newX, float newY);

	void SetLabel(string x);
	void SetState(string type);

	bool bIsinBounds(sf::Vector2f _vMousePosition);
	bool bIsPressed(int x = 1);

	int GetHeight();
	int GetWidth();

private:
	sf::RenderWindow* m_RenderWindow;

	sf::Texture m_IdleTexture;
	sf::Texture m_HoverTexture;
	sf::Texture m_ClickTexture;
	sf::Font m_Font;

	float X = 0.0f;
	float X2 = 0;
	float Y = 0;
	float Y2 = 0;

	int m_Adjustment = 0;

};

