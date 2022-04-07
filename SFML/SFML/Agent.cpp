#include "Agent.h"

Agent::Agent(float& _deltaTime, sf::Vector2i& _windowSize, sf::RenderWindow* _renderWindow, std::vector<Obstacle*>& _obstacleList) : m_DeltaTime(&_deltaTime), m_WindowSize(&_windowSize), m_RenderWindow(_renderWindow), m_Obsticles(&_obstacleList)
{
	Start();
}

Agent::~Agent()
{
	m_WindowSize = nullptr;
	m_DeltaTime = nullptr;
	m_RenderWindow = nullptr;
	m_Obsticles = nullptr;
}

void Agent::Start()
{
	m_SpriteTexture.loadFromFile("Resources/Textures/SpaceShip.png");

	m_Sprite.setTexture(m_SpriteTexture, true);
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2, m_Sprite.getGlobalBounds().height / 2);
	m_Sprite.setPosition((float)m_WindowSize->x / 2, (float)m_WindowSize->y / 2);
	m_Sprite.setScale({ 0.2f, 0.2f });

	m_Velocity = {0, -m_MaxSpeed};
	m_CollisionRect.setFillColor(sf::Color::Transparent);
	m_CollisionRect.setOutlineColor(sf::Color::Cyan);
	m_CollisionRect.setOutlineThickness(1);
	m_CollisionRect.setOrigin({ m_Sprite.getLocalBounds().width * 0.1f, 0 });
}

void Agent::Update()
{
	m_SteeringForce = {};
	Seek((sf::Vector2f)sf::Mouse::getPosition(*m_RenderWindow));
	//Wander(100, 20);
	Avoidence();
	ApplySteeringForce();
	Translate(m_Velocity * (*m_DeltaTime));
	LookAt(std::move(m_Velocity));
	LoopWithScreen();

	m_CollisionRect.setSize({ m_Sprite.getLocalBounds().width * 0.2f, -Mag(m_Velocity) * 1.5f });
	m_CollisionRect.setPosition(GetPosition());
	m_CollisionRect.setRotation(m_Sprite.getRotation());
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

sf::Vector2f Agent::GetPosition()
{
	return m_Sprite.getPosition();
}

sf::Vector2f Agent::GetVelocity()
{
	return m_Velocity;
}

void Agent::Translate(sf::Vector2f&& _translation)
{
	m_Sprite.setPosition(m_Sprite.getPosition().x + _translation.x, m_Sprite.getPosition().y + _translation.y);
}

void Agent::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Sprite, _states);

	_target.draw(m_CollisionRect, _states);

	sf::VertexArray velocity(sf::LinesStrip, 2);
	velocity[0].position = m_Sprite.getPosition();
	velocity[0].color = sf::Color::White;
	velocity[1].position = m_Sprite.getPosition() + m_Velocity;
	velocity[1].color = sf::Color::White;
	_target.draw(velocity, _states);

	sf::VertexArray steeringForce(sf::LinesStrip, 2);
	steeringForce[0].position = m_Sprite.getPosition() + m_Velocity;
	steeringForce[0].color = sf::Color::Red;
	steeringForce[1].position = m_Sprite.getPosition() + m_Velocity + m_SteeringForce;
	steeringForce[1].color = sf::Color::Red;
	_target.draw(steeringForce, _states);




}

void Agent::LoopWithScreen()
{
	if (m_Sprite.getPosition().x > (float)m_WindowSize->x )
	{
		m_Sprite.setPosition({ 0 ,m_Sprite.getPosition().y });
	}
	else if (m_Sprite.getPosition().x < 0)
	{
		m_Sprite.setPosition({ (float)m_WindowSize->x ,m_Sprite.getPosition().y });
	}

	if (m_Sprite.getPosition().y > (float)m_WindowSize->y)
	{
		m_Sprite.setPosition({ m_Sprite.getPosition().x ,0});
	}
	else if (m_Sprite.getPosition().y < 0)
	{
		m_Sprite.setPosition({ m_Sprite.getPosition().x ,(float)m_WindowSize->y});
	}
}

void Agent::LookAt(sf::Vector2f&& _direction)
{
	m_Sprite.setRotation(90.0f + ToDegrees(atan2(_direction.y, _direction.x)));
}

void Agent::ApplySteeringForce()
{
	Truncate(m_SteeringForce, m_MaxForce);
	m_Velocity += m_SteeringForce * *m_DeltaTime;
	Truncate(m_Velocity, m_MaxSpeed);
}

void Agent::Seek(sf::Vector2f _targetPos)
{
	sf::Vector2f desiredVelocity = Normalize(_targetPos - GetPosition()) * m_MaxSpeed;
	m_SteeringForce += desiredVelocity - m_Velocity;

}

void Agent::Flee(sf::Vector2f _targetPos)
{
	sf::Vector2f desiredVelocity = Normalize(GetPosition() - _targetPos) * m_MaxSpeed;
	m_SteeringForce += desiredVelocity - m_Velocity;
}

void Agent::Pursuit(Agent& _otherAgent)
{
	Seek(_otherAgent.GetVelocity() + _otherAgent.GetPosition());
}

void Agent::Evade(Agent& _otherAgent)
{
	Flee(_otherAgent.GetVelocity() + _otherAgent.GetPosition());
}

void Agent::Wander(float _wanderDistance, float _wanderRadius)
{
	float x = (Normalize(std::move(m_Velocity)).x * _wanderDistance) + cosf(ToRadians(m_WanderAngle)) * _wanderRadius;
	float y = (Normalize(std::move(m_Velocity)).y * _wanderDistance) + sinf(ToRadians(m_WanderAngle)) * _wanderRadius;

	Seek(sf::Vector2f{x,y} + GetPosition());

	if (m_WanderAngle < -90)
	{
		m_WanderingLeft = false;
	}
	if (m_WanderAngle > 90)
	{
		m_WanderingLeft = true;
	}
	if (m_WanderingLeft)
	{
		m_WanderAngle -= *m_DeltaTime * (float)(rand() % (int)_wanderRadius);
	}
	else
	{
		m_WanderAngle += *m_DeltaTime * (float)(rand() % (int)_wanderRadius);
	}
}

void Agent::Avoidence()
{
	float playerWidth = m_Sprite.getGlobalBounds().width / 2;
	float direction;
	for (auto& obstacle : *m_Obsticles)
	{
		// Obstacle In Front Of Enemy
		if (Dot(Normalize(obstacle->GetPosition() - GetPosition()), Normalize(std::move(m_Velocity))) > 0)
		{
			// Obstacle In Collision Box
			if (m_CollisionRect.getGlobalBounds().intersects(obstacle->GetGlobalBounds()))
			{
				direction = AngleDir(Normalize(obstacle->GetPosition() - GetPosition()), Normalize(std::move(m_Velocity)));
				// Obstacle On Right
				if (direction >= 0)
				{
					Print("On Right");
					m_SteeringForce += CWPerp(m_Velocity);
				}
				// Obstacle On Left
				else
				{
					Print("On Left");
					m_SteeringForce += CCWPerp(m_Velocity);
				}
			}
		}
	}
}
