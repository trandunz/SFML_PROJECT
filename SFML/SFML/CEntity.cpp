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
	m_sName = "Default";
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
	/*m_oBody.move(Movement());*/
}

void CEntity::Render()
{
	m_rRenderWindow->draw(m_oBody);
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
