#include "CEnemy.h"
#include <iostream>
#include "CMath.h"

CEnemy::CEnemy()
{
	CEnemy::Start();
}

CEnemy::CEnemy(sf::RenderWindow* _renderWindow)
{
	m_rRenderWindow = _renderWindow;
	CEnemy::Start();
}

CEnemy::CEnemy(sf::RenderWindow* _renderWindow, ENTITY_TYPES _TYPE)
{
	m_eEntityType = _TYPE;
	m_rRenderWindow = _renderWindow;
	
	CEnemy::Start();
}

CEnemy::CEnemy(sf::RenderWindow* _renderWindow, ENTITY_TYPES _TYPE, sf::Vector2f _spawnPosition)
{
	m_eEntityType = _TYPE;
	m_rRenderWindow = _renderWindow;
	m_oBody.setPosition(_spawnPosition);
	CEnemy::Start();
}

CEnemy::CEnemy(ENTITY_TYPES _TYPE)
{
	m_eEntityType = _TYPE;
	CEnemy::Start();
}

CEnemy::CEnemy(sf::Vector2f _spawnPosition)
{
	m_oBody.setPosition(_spawnPosition);
	CEnemy::Start();
}

CEnemy::~CEnemy()
{
}

void CEnemy::Start()
{
	switch (m_eEntityType)
	{
	case WEREWOLF:
	{
		m_sName = ("WEREWOLF");
		m_fMoveSpeed = 15.0f + BaseMoveSpeed;
		m_fAttackDamage = 5.0f;
		if (m_tTexture.loadFromFile("Images/WareWolf.png"))
		{
			m_tTexture.setSmooth(true);
			std::cout << "Loaded ZOMBIE Texture" << std::endl;
		}
		m_oBody.setTexture(m_tTexture);
		m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
		m_oBody.setScale(0.5f, 0.5f);
		break;
	}
	case ZOMBIE:
	{
		m_sName = ("ZOMBIE");
		m_fMoveSpeed = BaseMoveSpeed - 15.0f;
		m_fAttackDamage = 5.0f;
		if (m_tTexture.loadFromFile("Images/Zombie.png"))
		{
			m_tTexture.setSmooth(true);
			std::cout << "Loaded ZOMBIE Texture" << std::endl;
		}
		m_oBody.setTexture(m_tTexture);
		m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
		m_oBody.setScale(0.5f, 0.5f);
		break;
	}
	case VAMPIRE:
	{
		m_sName = ("VAMPIRE");
		m_fMoveSpeed = BaseMoveSpeed - 20.0f;
		m_fAttackDamage = 5.0f;
		if (m_tTexture.loadFromFile("Images/Vampire.png"))
		{
			m_tTexture.setSmooth(true);
			std::cout << "Loaded VAMPIRE Texture" << std::endl;
		}
		m_oBody.setTexture(m_tTexture);
		m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
		m_oBody.setScale(0.5f, 0.5f);
		break;
	}
	case HUMAN:
	{
		m_sName = ("HUMAN");
		m_fMoveSpeed = 25.0f + BaseMoveSpeed;
		m_fAttackDamage = 5.0f;
		if (m_tTexture.loadFromFile("Images/Player.png"))
		{
			m_tTexture.setSmooth(true);
			std::cout << "Loaded HUMAN Texture" << std::endl;
		}
		m_oBody.setTexture(m_tTexture);
		m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
		m_oBody.setScale(0.5f, 0.5f);
		break;
	}
	default:
	{
		m_sName = ("DEFAULT");
		m_fMoveSpeed = 25.0f + BaseMoveSpeed;
		m_fAttackDamage = 5.0f;
		break;
	}
	}
	m_fCurrentMoveSpeed = m_fMoveSpeed;
}

void CEnemy::Update()
{
	TempPosition = Position;
	Movement(sf::Vector2f(0.0f, 0.0f));
	m_oBody.move(m_fVelocity * m_fCurrentMoveSpeed * GetDeltaTime().asSeconds());
	
}

sf::Vector2f CEnemy::Movement(sf::Vector2f _spawnPosition)
{
	Position = sf::Vector2f(m_oBody.getPosition().x, m_oBody.getPosition().y);
	m_oBody.move(_spawnPosition);
	m_fVelocity = CMath::Normalize(sf::Vector2f(m_vTarget.getPosition().x - m_oBody.getPosition().x, m_vTarget.getPosition().y - m_oBody.getPosition().y));
	if (m_fVelocity.y > 0.5)
	{
		// moving left
		if (m_eEntityType == ZOMBIE)
		{
			m_tTexture.loadFromFile("Images/Zombie.png");
			m_oBody.setTexture(m_tTexture);
		}
		else if (m_eEntityType == VAMPIRE)
		{
			m_tTexture.loadFromFile("Images/Vampire.png");
			m_oBody.setTexture(m_tTexture);
		}
		else if (m_eEntityType == WEREWOLF)
		{
			m_tTexture.loadFromFile("Images/WareWolf.png");
			m_oBody.setTexture(m_tTexture);
		}

	}
	if (m_fVelocity.y < -0.5)
	{
		// moving left
		if (m_eEntityType == ZOMBIE)
		{
			m_tTexture.loadFromFile("Images/ZombieBack.png");
			m_oBody.setTexture(m_tTexture);
		}
		else if (m_eEntityType == VAMPIRE)
		{
			m_tTexture.loadFromFile("Images/VampireBack.png");
			m_oBody.setTexture(m_tTexture);
		}
		else if (m_eEntityType == WEREWOLF)
		{
			m_tTexture.loadFromFile("Images/WareWolfBack.png");
			m_oBody.setTexture(m_tTexture);
		}

	}
	
	if (m_fVelocity.x < -0.5)
	{
		// moving left
		if (m_eEntityType == ZOMBIE)
		{
			m_tTexture.loadFromFile("Images/ZombieSideProfile.png");
			m_oBody.setTexture(m_tTexture);
		}
		else if (m_eEntityType == VAMPIRE)
		{
			m_tTexture.loadFromFile("Images/VampireSideProfile.png");
			m_oBody.setTexture(m_tTexture);
		}
		else if (m_eEntityType == WEREWOLF)
		{
			m_tTexture.loadFromFile("Images/WareWolfSideProfile.png");
			m_oBody.setTexture(m_tTexture);
		}
		
	}
	if (m_fVelocity.x > 0.5)
	{
		// moving left
		if (m_eEntityType == ZOMBIE)
		{
			m_tTexture.loadFromFile("Images/ZombieSideProfile2.png");
			m_oBody.setTexture(m_tTexture);
		}
		else if (m_eEntityType == VAMPIRE)
		{
			m_tTexture.loadFromFile("Images/VampireSideProfile2.png");
			m_oBody.setTexture(m_tTexture);
		}
		else if (m_eEntityType == WEREWOLF)
		{
			m_tTexture.loadFromFile("Images/WareWolfSideProfile2.png");
			m_oBody.setTexture(m_tTexture);
		}

	}
	

	/*std::cout << m_fVelocity.x << std::endl;
	std::cout << m_fVelocity.y << std::endl;*/

	return(m_fVelocity);
}

void CEnemy::LookAt(sf::Sprite _Entity)
{
	sf::Vector2f curPos = m_oBody.getPosition();
	sf::Vector2f position = _Entity.getPosition();

	// now we have both the sprite position and the cursor
	// position lets do the calculation so our sprite will
	// face the position of the mouse
	const float PI = 3.1415926f;

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;

	float rotation = (atan2(dy, dx)) * 180 / PI;

	m_oBody.setRotation(rotation);
}

void CEnemy::Render()
{
	m_rRenderWindow->draw(m_oBody);
}

void CEnemy::CheckCollision(CPlayer* _object)
{
	if (m_oBody.getGlobalBounds().intersects(_object->GetSprite().getGlobalBounds()))
	{
		m_oBody.setPosition(TempPosition);
	}
	/*sf::FloatRect overlap;
	if (m_oBody.getGlobalBounds().intersects(_object->GetSprite().getGlobalBounds(), overlap))
	{
		m_fCurrentMoveSpeed = 0.0f;
		auto collisionNormal = m_oBody.getPosition() - _object->GetSprite().getPosition();
		auto manifold = getManifold(overlap, collisionNormal);
		resolveCollision(manifold);
	}
	else
	{
		m_fCurrentMoveSpeed = m_fMoveSpeed;
	}*/
}

void CEnemy::CheckCollision(sf::Sprite _object)
{
	if(m_oBody.getGlobalBounds().intersects(_object.getGlobalBounds()))
	{
		m_oBody.setPosition(TempPosition);
	}
	/*sf::FloatRect overlap;
	if (m_oBody.getGlobalBounds().intersects(_object.getGlobalBounds(), overlap))
	{
		m_fCurrentMoveSpeed = 0.0f;
		
		auto collisionNormal = m_oBody.getPosition() - _object.getPosition();
		
		auto manifold = getManifold(overlap, collisionNormal);
		m_oBody.setPosition(Position);
		resolveCollision(manifold);
		
	}
	else
	{
		m_fCurrentMoveSpeed = m_fMoveSpeed;
	}*/
}

sf::Sprite CEnemy::GetSprite()
{
	return m_oBody;
}




