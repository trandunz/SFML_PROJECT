#pragma once
#include <SFML/graphics.hpp>
class Player
{
public:
	Player(sf::RenderWindow* _renderWindow);
	Player(sf::RenderWindow* _renderWindow, sf::Vector2f __origin);
	~Player();
	void Start();
	void Update();
	void Draw();
	sf::Vector2f Movement();
	sf::View PlayerView();

	sf::CircleShape m_oPlayerBody;

	float m_dSpeed;

private:
	sf::RenderWindow* m_rRenderWindow;


	
	const float m_fFPS = 60.0f;

	sf::Clock clClock;

	bool redraw;

};

