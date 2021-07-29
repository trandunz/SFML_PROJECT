#pragma once
#pragma <disable : 26812> // SILENCE MINION!
#include <SFML/Graphics.hpp>
#include "CEntity.h"
class CPlayer : protected CEntity
{
public:
	CPlayer();
	CPlayer(sf::RenderWindow* _renderWindow);
	~CPlayer();
	void Start();
	void Update();
	void Render();
	sf::Vector2f Movement();
	void LookAtMouse();

	sf::View PlayerView();
	sf::Sprite GetSprite();

private:
	sf::Sprite m_oBody;
};

