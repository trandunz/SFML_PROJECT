#include "CEntity.h"

CEntity::CEntity()
{
	m_rRenderWindow = nullptr;
	m_sName = "Default";
	m_fHealth = 100.0f;
	m_fAttackDamage = 10.0f;
	m_oBody.setRadius(10.0f);
	Start();
}

CEntity::CEntity(sf::RenderWindow* _rRenderWindow)
{
	m_rRenderWindow = _rRenderWindow;
	m_sName = "Human";
	m_fHealth = 100.0f;
	m_fAttackDamage = 10.0f;
	m_oBody.setRadius(10.0f);
	Start();
}

CEntity::~CEntity()
{
	m_rRenderWindow = nullptr;
	delete m_rRenderWindow;
}

void CEntity::Start()
{
	m_oBody.setRadius(8.0f);
	m_oBody.setFillColor(sf::Color::Red);
	m_oBody.setOrigin(sf::Vector2f(0.0f, 0.0f));
}

void CEntity::Update()
{
	Position = sf::Vector2f(m_oBody.getPosition().x, m_oBody.getPosition().y);
}

void CEntity::Render()
{
	m_rRenderWindow->draw(m_oBody);
}

bool CEntity::CheckCollision(sf::Sprite _object)
{
	if (m_oBody.getGlobalBounds().intersects(_object.getGlobalBounds()))
	{
		// A collision happened.
		m_oBody.setPosition(Position);
		return true;
	}
	else
	{
		Position = sf::Vector2f(m_oBody.getPosition().x, m_oBody.getPosition().y);
		return false;
	}
}

sf::Time CEntity::GetDeltaTime()
{
	return DeltaTime;
}

void CEntity::SetDeltaTime(sf::Time _deltaTime)
{
	DeltaTime = _deltaTime;
}

void CEntity::Attack()
{

}

//sf::Vector2f CEntity::Movement()
//{
//	return sf::Vector2f(0.0f,0.0f);
//}

float CEntity::Heal(float _amount)
{
	m_fHealth += _amount;
	return m_fHealth;
}

void CEntity::TakeDamage(float _amount)
{
	m_fHealth -= _amount;
}
