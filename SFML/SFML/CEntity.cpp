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

void CEntity::CheckCollision(sf::Sprite _object)
{
	if (m_oBody.getGlobalBounds().intersects(_object.getGlobalBounds()))
	{
		if (m_fVelocity.y > 0.5)
		{
			m_fVelocity.y -= 1.0f;

		}
		if (m_fVelocity.y < -0.5)
		{
			// moving left
			m_fVelocity.y += 1.0f;

		}

		if (m_fVelocity.x < -0.5)
		{
			// moving left
			m_fVelocity.x += 1.0f;

		}
		if (m_fVelocity.x > 0.5)
		{
			// moving left
			m_fVelocity.x -= 1.0f;

		}
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

sf::Vector2f CEntity::Reflect(sf::Vector2f _velocity, sf::Vector2f _normal)
{
	return -2.f * CMath::Dot(_velocity, _normal) * _normal + _velocity;
}

sf::Vector3f CEntity::getManifold(sf::FloatRect overlap, sf::Vector2f collisionNormal)
{
	sf::Vector3f manifold;

	if (overlap.width < overlap.height)
	{
		manifold.x = (collisionNormal.x < 0) ? 1.f : -1.f;
		manifold.z = overlap.width;
	}
	else
	{
		manifold.y = (collisionNormal.y < 0) ? 1.f : -1.f;
		manifold.z = overlap.height;
	}

	return manifold;
}

void CEntity::resolveCollision(sf::Vector3f manifold)
{
	//move the ball out of the solid object by the penetration amount
	sf::Vector2f normal(manifold.x, manifold.y);
	m_oBody.move(normal * manifold.z);
	

	//reflect the current velocity to make the ball bounce
	m_fVelocity = Reflect(m_fVelocity, normal);
}
