#include "Agent.h"

Agent::Agent(float& _deltaTime, sf::Vector2i& _windowSize, sf::RenderWindow* _renderWindow) : m_DeltaTime(&_deltaTime), m_WindowSize(&_windowSize), m_RenderWindow(_renderWindow)
{
	Start();
}

Agent::~Agent()
{
	m_WindowSize = nullptr;
	m_DeltaTime = nullptr;
	m_RenderWindow = nullptr;
}

void Agent::Start()
{
	m_SpriteTexture.loadFromFile("Resources/Textures/SpaceShip.png");

	m_Sprite.setTexture(m_SpriteTexture, true);
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2, m_Sprite.getGlobalBounds().height / 2);
	m_Sprite.setPosition((float)m_WindowSize->x / 2, (float)m_WindowSize->y / 2);
	m_Sprite.setScale({ 0.2f, 0.2f });

	m_Velocity = {0, -m_MaxSpeed};
}

void Agent::Update()
{
	Seek((sf::Vector2f)sf::Mouse::getPosition(*m_RenderWindow));
	Translate(m_Velocity * (*m_DeltaTime));
	LookAt(std::move(m_Velocity));
}

void Agent::HandleInput()
{
	/*for (auto& key : KeyMap)
	{
		if (key.second)
		{
			switch (key.first)
			{
			default:
				break;
			}
		}
	}*/
}

void Agent::Translate(sf::Vector2f&& _translation)
{
	m_Sprite.setPosition(m_Sprite.getPosition().x + _translation.x, m_Sprite.getPosition().y + _translation.y);
}

void Agent::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Sprite, _states);
}

void Agent::LookAt(sf::Vector2f&& _direction)
{
	m_Sprite.setRotation(90.0f + atan2(_direction.y, _direction.x) * (180.0f / (float)PI));
}

void Agent::Seek(sf::Vector2f _targetPos)
{
	sf::Vector2f desiredVelocity = Normalize(_targetPos - m_Sprite.getPosition()) * m_MaxSpeed;
	sf::Vector2f steeringForce = desiredVelocity - m_Velocity;
	Truncate(steeringForce, m_MaxForce);
	if (Mag(steeringForce) >= 0.001f)
	{
		m_Velocity += steeringForce * *m_DeltaTime;
		Truncate(m_Velocity, m_MaxSpeed);
	}
}

void Agent::Flee(sf::Vector2f _targetPos)
{
	sf::Vector2f desiredVelocity = Normalize(m_Sprite.getPosition() - _targetPos) * m_MaxSpeed;
	sf::Vector2f steeringForce = desiredVelocity - m_Velocity;
	Truncate(steeringForce, m_MaxForce);
	if (Mag(steeringForce) >= 0.001f)
	{
		m_Velocity += steeringForce * *m_DeltaTime;
		Truncate(m_Velocity, m_MaxSpeed);
	}
}
