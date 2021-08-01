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
	void CheckCollision(sf::RectangleShape _object);
	void CheckCollision(sf::Sprite _object);
	void Movement();
	void LookAtMouse();

	bool HealthCheck();
	void SetMousePosition(sf::Vector2f _position);
	sf::Vector2f GetMousePosition();

	sf::View PlayerView();
	sf::Sprite GetSprite();

private:
	CItem* m_CurrentItem;
	CItem* m_CurrentShield;
	sf::Vector2f m_vMousePosition;
	sf::Sprite m_oBody;
};

