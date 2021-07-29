#include "CEnemy.h"
#include <iostream>

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
		m_fMoveSpeed = 3.0f;
		m_fAttackDamage = 5.0f;
		if (m_tTexture.loadFromFile("Images/WareWolf.png"))
		{
			m_tTexture.setSmooth(true);
			std::cout << "Loaded ZOMBIE Texture" << std::endl;
		}
		m_oBody.setTexture(m_tTexture);
		m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
		m_oBody.setScale(0.5f, 0.5f);
		return;
	}
	case ZOMBIE:
	{
		m_sName = ("ZOMBIE");
		m_fMoveSpeed = 3.0f;
		m_fAttackDamage = 5.0f;
		if (m_tTexture.loadFromFile("Images/Zombie.png"))
		{
			m_tTexture.setSmooth(true);
			std::cout << "Loaded ZOMBIE Texture" << std::endl;
		}
		m_oBody.setTexture(m_tTexture);
		m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
		m_oBody.setScale(0.5f, 0.5f);
		return;
	}
	case VAMPIRE:
	{
		m_sName = ("VAMPIRE");
		m_fMoveSpeed = 3.0f;
		m_fAttackDamage = 5.0f;
		if (m_tTexture.loadFromFile("Images/Vampire.png"))
		{
			m_tTexture.setSmooth(true);
			std::cout << "Loaded VAMPIRE Texture" << std::endl;
		}
		m_oBody.setTexture(m_tTexture);
		m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
		m_oBody.setScale(0.5f, 0.5f);
		return;
	}
	case HUMAN:
	{
		m_sName = ("HUMAN");
		m_fMoveSpeed = 3.0f;
		m_fAttackDamage = 5.0f;
		if (m_tTexture.loadFromFile("Images/Player.png"))
		{
			m_tTexture.setSmooth(true);
			std::cout << "Loaded HUMAN Texture" << std::endl;
		}
		m_oBody.setTexture(m_tTexture);
		m_oBody.setOrigin(m_oBody.getGlobalBounds().width / 2, m_oBody.getGlobalBounds().height / 2);
		m_oBody.setScale(0.5f, 0.5f);
		return;
	}
	default:
	{
		m_sName = ("DEFAULT");
		m_fMoveSpeed = 3.0f;
		m_fAttackDamage = 5.0f;
		return;
	}
	}

}

void CEnemy::Movement(sf::Vector2f _spawnPosition)
{
	m_oBody.setPosition(_spawnPosition);
}

void CEnemy::Render()
{
	m_rRenderWindow->draw(m_oBody);
}




