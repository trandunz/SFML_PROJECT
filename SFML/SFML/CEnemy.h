#pragma once
#pragma <disable : 26812> // SILENCE MINION!
#include <SFML/Graphics.hpp>
#include "CEntity.h"
#include "CPlayer.h"
class CEnemy : public CEntity
{
public:
	CEnemy();
	CEnemy(sf::RenderWindow* _renderWindow);
	CEnemy(sf::RenderWindow* _renderWindow, ENTITY_TYPES _TYPE);
	CEnemy(sf::RenderWindow* _renderWindow, ENTITY_TYPES _TYPE, sf::Vector2f _spawnPosition);
	CEnemy(ENTITY_TYPES _TYPE);
	CEnemy(sf::Vector2f _spawnPosition);
	~CEnemy();

	void Start();
	void Update();

	sf::Vector2f Movement(sf::Vector2f _spawnPosition);
	void LookAt(sf::Sprite _Entity);

	void Render();

	void CheckCollision(CPlayer* _object);
	void CheckCollision(sf::Sprite _object);

	sf::Sprite GetSprite();

	sf::Sprite m_vTarget;

private:
	sf::Sprite m_oBody;
};

