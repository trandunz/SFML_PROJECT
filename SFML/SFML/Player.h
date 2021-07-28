#pragma once
#include <SFML/graphics.hpp>
class Player
{
public:
	Player(sf::RenderWindow* _renderWindow);
	~Player();
	void Start();
	void Update();
	sf::Vector2f Movement();
	sf::View PlayerView();

	void SetView(sf::View _view);

private:
	sf::RenderWindow* m_rRenderWindow;
	sf::CircleShape m_oPlayerBody;
	const float m_fFPS = 60.0f;

	sf::Clock clClock;

	bool redraw;

};

