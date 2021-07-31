#pragma once
#pragma <disable : 26812> // SILENCE MINION!
#include <SFML/Graphics.hpp>
#include "CEntity.h"
class CPlayer : public CEntity
{
public:
	CPlayer();
	CPlayer(sf::RenderWindow* _renderWindow);
	CPlayer(sf::RenderWindow* _renderWindow, sf::Vector2f _spawnPoint);
	~CPlayer();
	void Start();
	void Update();
	void Render();
	bool CheckCollision(sf::RectangleShape _object);
	bool CheckCollision(sf::Sprite _object);
	void Movement();
	void LookAtMouse();

	bool HealthCheck();

	sf::View PlayerView();
	sf::Sprite GetSprite();

private:
	sf::Sprite m_oBody;
};

