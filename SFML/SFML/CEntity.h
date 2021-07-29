#pragma once
#pragma <disable : 26812> // SILENCE MINION!

#include <SFML/Graphics.hpp>
#include <string>


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

	virtual void Attack();
	/*sf::Vector2f Movement();*/
	virtual float Heal(float _amount);
	virtual void TakeDamage(float _amount);

	ENTITY_TYPES m_eEntityType = ENTITY_TYPES::DEFAULT;
	sf::CircleShape m_oBody;

protected:
	sf::RenderWindow* m_rRenderWindow;
	float m_fMoveSpeed;
	float m_fHealth;
	float m_fAttackDamage;
	std::string m_sName;
	sf::Texture m_tTexture;
};

