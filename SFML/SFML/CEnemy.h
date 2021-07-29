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
	void Update();

	sf::Vector2f Movement(sf::Vector2f _spawnPosition);
	void LookAt(sf::Sprite _Entity);

	void Render();

	sf::Sprite m_vTarget;

private:
	sf::Sprite m_oBody;
};

