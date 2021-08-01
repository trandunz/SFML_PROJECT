#pragma once
#pragma <disable : 26812> // SILENCE MINION!

#include <SFML/Graphics.hpp>
#include <string>
#include "CMath.h"
#include "CItem.h"


class CEntity
{
public:
	enum ENTITY_TYPES
	{
		WEREWOLF,
		ZOMBIE,
		VAMPIRE,
		HUMAN,
		DEFAULT
	};

	CEntity();
	CEntity(sf::RenderWindow* m_rRenderWindow);
	virtual ~CEntity();

	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void CheckCollision(sf::Sprite _object);

	sf::Time GetDeltaTime();
	void SetDeltaTime(sf::Time _deltaTime);

	virtual void Attack();
	/*sf::Vector2f Movement();*/
	virtual float Heal(float _amount);
	virtual void TakeDamage(float _amount);

	sf::Vector2f Reflect(sf::Vector2f velocity, sf::Vector2f normal);
	sf::Vector3f getManifold(sf::FloatRect overlap, sf::Vector2f collisionNormal);
	void resolveCollision(sf::Vector3f manifold);

	void PickUpItem(CItem* _item);


	ENTITY_TYPES m_eEntityType = ENTITY_TYPES::DEFAULT;
	sf::CircleShape m_oBody;

protected:
	sf::Vector2f m_fVelocity;
	const int BaseMoveSpeed = 50;
	sf::Vector2f Position;
	sf::Vector2f TempPosition;
	sf::Time DeltaTime;
	sf::RenderWindow* m_rRenderWindow;
	sf::Window* m_wWindow;
	float m_fMoveSpeed;
	float m_fCurrentMoveSpeed;
	float m_fHealth;
	float m_fAttackDamage;
	std::string m_sName;
	sf::Texture m_tTexture;
};

