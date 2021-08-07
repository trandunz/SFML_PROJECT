#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class CCanvas
{
public:
	sf::Vector2f m_Size;
	sf::RectangleShape m_Canvas;
	sf::Sprite m_BackGround;
	sf::Texture m_BGTexture;
	
	CCanvas();
	CCanvas(sf::RenderWindow* _window, sf::Vector2f _size);
	~CCanvas();
	void SetRenderWindow(sf::RenderWindow*);
	sf::RenderWindow* GetRenderWindow();

	void Start();
	void Update();
	virtual void Render();

protected:
	sf::RenderWindow* m_RenderWindow;
};

