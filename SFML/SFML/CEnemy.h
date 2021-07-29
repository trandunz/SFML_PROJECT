#pragma once
#pragma <disable : 26812> // SILENCE MINION!
#include <SFML/Graphics.hpp>
#include "CEntity.h"
class CEnemy : protected CEntity
{
public:
	CEnemy();
	CEnemy(sf::RenderWindow* _renderWindow);
	CEnemy(sf::RenderWindow* _renderWindow, ENTITY_TYPES _TYPE);
	CEnemy(ENTITY_TYPES _TYPE);
	CEnemy(sf::Vector2f _spawnPosition);
	~CEnemy();

	void Start();
	void Movement(sf::Vector2f _spawnPosition);

	void Render();

private:
	sf::Sprite m_oBody;
};

