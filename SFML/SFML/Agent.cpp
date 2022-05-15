// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Agent.cpp 
// Description : Agent Implementation File
// Author : William Inman
// Mail : william.inman@mds.ac.nz

#include "Agent.h"

Agent::Agent(sf::Vector2i _initialPosition, float& _deltaTime, sf::Vector2i& _windowSize, sf::RenderWindow* _renderWindow, std::vector<Obstacle*>& _obstacleList, std::vector<Agent*>& _otherAgents) : m_DeltaTime(&_deltaTime), m_WindowSize(&_windowSize), m_RenderWindow(_renderWindow), m_Obsticles(&_obstacleList), m_OtherAgents(&_otherAgents)
{
	Start();
	m_Sprite.setPosition((sf::Vector2f)_initialPosition);
	
}

Agent::~Agent()
{
	m_WindowSize = nullptr;
	m_DeltaTime = nullptr;
	m_RenderWindow = nullptr;
	m_Obsticles = nullptr;
	m_OtherAgents = nullptr;
}

void Agent::Start()
{
	SetOriginToCentre(m_Sprite);

	m_Velocity = {0, -m_MaxSpeed};
	m_CollisionRect.setOrigin({ m_Sprite.getLocalBounds().width / 2, 0 });
	m_CollisionRect.setFillColor(sf::Color::Transparent);
	m_CollisionRect.setOutlineColor(sf::Color::Cyan);
	m_CollisionRect.setOutlineThickness(1);
	

	m_NeighborCircle.setFillColor(sf::Color::Transparent);
	m_NeighborCircle.setOutlineColor(sf::Color::Green);
	m_NeighborCircle.setOutlineThickness(1);
	m_NeighborCircle.setPointCount(360);
	m_NeighborCircle.setRadius(m_NeighborhoodRadius);

	SetOriginToCentre(m_NeighborCircle);
}

void Agent::Update()
{

	if (m_Sprite.getPosition().x > m_WindowSize->x + 10 || 
		m_Sprite.getPosition().x < -10 ||
		m_Sprite.getPosition().y > m_WindowSize->y + 10 ||
		m_Sprite.getPosition().y < -10)
	{
		m_Sprite.setPosition((float)m_WindowSize->x / 2, (float)m_WindowSize->y / 2);
	}
	sf::Vector2f mousepos = (sf::Vector2f)sf::Mouse::getPosition(*m_RenderWindow);
	sf::Vector2f steeringForce{ 0.0f,0.0f };
	if (m_IsFleeing)
	{
		steeringForce += Flee(mousepos);
	}
	if (m_IsWander)
	{
		steeringForce += Wander(100, 20);
	}
	if (m_IsEvade)
	{ 
		Agent* nearestAgent = GetNearestAgent();
		if (nearestAgent->GetPosition() == GetPosition())
			steeringForce += Wander(100, 20);
		else
			steeringForce += Evade(*nearestAgent);
	}
	if (m_IsPursuit)
	{
		Agent* nearestAgent = GetNearestAgent();
		if (nearestAgent->GetPosition() == GetPosition())
			steeringForce += Wander(100, 20);
		else
			steeringForce += Pursuit(*nearestAgent);
	}
	if (m_IsSeeking)
	{
		steeringForce += Seek(mousepos);
	}
	if (m_IsArriving)
	{
		steeringForce += Arrive(mousepos);
		m_Velocity = Truncate(m_Velocity + steeringForce, m_MaxSpeed);
	}
	if (m_IsSeperation)
	{
		steeringForce += Seperation();
	}
	if (m_IsAlignment)
	{
		steeringForce += Alignment();
	}
	if (m_IsCohesion)
	{
		steeringForce += Cohesion();
	}
	if (m_IsFlocking)
	{
		steeringForce += Alignment();
		steeringForce += Cohesion();
		steeringForce += Seperation() * 1.5f;
	}
	if (m_LeaderFollowing)
	{
		if (m_IsLeader)
			steeringForce += Seek((sf::Vector2f)sf::Mouse::getPosition(*m_RenderWindow));
		else
			steeringForce += LeaderFollowing();
	}
	if (Mag(steeringForce) <= 0)
	{
		steeringForce += Wander(100, 20);
	}
	if (m_IsAvoidence)
	{
		steeringForce += Avoidence() * 5.0f;
	}

	ApplyForce(steeringForce);
	m_Velocity += m_Acceleration * (*m_DeltaTime);
	Truncate(m_Velocity, m_MaxSpeed);
	Translate(m_Velocity * (*m_DeltaTime));
	LookAt(std::move(m_Velocity));
	LoopWithScreen();
	m_Acceleration = { 0.0f,0.0f };


	m_CollisionRect.setSize({ m_Sprite.getLocalBounds().width, -Mag(m_Velocity) * 1.5f });
	m_CollisionRect.setPosition(GetPosition());
	m_CollisionRect.setRotation(m_Sprite.getRotation());
	
	if (m_DebugLines)
		m_NeighborCircle.setPosition(GetPosition());
}

void Agent::ToggleDebugLines()
{
	m_DebugLines = !m_DebugLines;
}

void Agent::SetDebugLines(bool _isDebug)
{
	m_DebugLines = _isDebug;
}

bool Agent::IsDebug()
{
	return m_DebugLines;
}

sf::FloatRect Agent::GetGlobalBounds()
{
	return m_Sprite.getGlobalBounds();
}

sf::Vector2f Agent::GetPosition()
{
	return m_Sprite.getPosition();
}

sf::Vector2f Agent::GetVelocity()
{
	return m_Velocity;
}

sf::Vector2f Agent::GetInverseVelocity()
{
	return -m_Velocity;
}

sf::RectangleShape Agent::GetCollisionRect()
{
	return m_CollisionRect;
}

int Agent::GetID()
{
	return m_AgentID;
}

void Agent::SetID(int _newID)
{
	m_AgentID = _newID;
}

void Agent::Translate(sf::Vector2f&& _translation)
{
	m_Sprite.setPosition(m_Sprite.getPosition().x + _translation.x, m_Sprite.getPosition().y + _translation.y);
}


void Agent::SetState(char&& _state)
{
	m_IsFleeing = false;
	m_IsSeeking = false;
	m_IsPursuit = false;
	m_IsEvade = false;
	m_IsWander = false;
	m_IsSeperation = false;
	m_IsAlignment = false;
	m_IsCohesion = false;
	m_IsFlocking = false;
	m_IsArriving = false;
	m_LeaderFollowing = false;
	switch (std::move(_state))
	{
	case 'f':
	{
		m_IsFleeing = true;
		break;
	}
	case 's':
	{
		m_IsSeeking = true;
		break;
	}
	case 'p':
	{
		m_IsPursuit = true;
		break;
	}
	case 'e':
	{
		m_IsEvade = true;
		break;
	}
	case 'w':
	{
		m_IsWander = true;
		break;
	}
	case 'n':
	{
		m_IsSeperation = true;
		break;
	}
	case 'a':
	{
		m_IsAlignment = true;
		break;
	}
	case 'c':
	{
		m_IsCohesion = true;
		break;
	}
	case 'g':
	{
		m_IsFlocking = true;
		break;
	}
	case 'r':
	{
		m_IsArriving = true;
		break;
	}
	case 'l':
	{
		m_LeaderFollowing = true;
		break;
	}
	default:
		break;
	}
}

char Agent::GetState()
{
	if (m_IsSeeking)
	{
		return 's';
	}
	else if (m_IsFleeing)
	{
		return 'f';
	}
	else if (m_IsPursuit)
	{
		return 'p';
	}
	else if (m_IsEvade)
	{
		return 'e';
	}
	else if (m_IsWander)
	{
		return 'w';
	}
	else if (m_IsSeperation)
	{
		return 'n';
	}
	else if (m_IsAlignment)
	{
		return 'a';
	}
	else if (m_IsCohesion)
	{
		return 'c';
	}
	else if (m_IsFlocking)
	{
		return 'g';
	}
	else if (m_IsArriving)
	{
		return 'r';
	}
	else if (m_LeaderFollowing)
	{
		return 'l';
	}
	return '!';
}

void Agent::ToggleAvoidence()
{
	m_IsAvoidence = !m_IsAvoidence;
}

void Agent::SetAvoidence(bool _isAvoidence)
{
	m_IsAvoidence = _isAvoidence;
}

bool Agent::IsAvoiding()
{
	return m_IsAvoidence;
}

bool Agent::IsLeader()
{
	return m_IsLeader;
}

void Agent::ToggleLeader()
{
	for (auto& agent : *m_OtherAgents)
	{
		agent->SetLeader(false);
	}
	m_IsLeader = true;
}

void Agent::SetLeader(bool&& _isLeader)
{
	m_IsLeader = _isLeader;
}

void Agent::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Sprite, _states);

	if (m_DebugLines)
	{
		_target.draw(m_NeighborCircle, _states);

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
		steeringForce[1].position = m_Sprite.getPosition() + m_Velocity + m_Acceleration;
		steeringForce[1].color = sf::Color::Red;
		_target.draw(steeringForce, _states);
	}
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

void Agent::ApplyForce(sf::Vector2f _force)
{
	m_Acceleration += _force;
}

sf::Vector2f Agent::Seek(sf::Vector2f _targetPos)
{
	sf::Vector2f desiredVelocity = Normalize(_targetPos - GetPosition()) * m_MaxSpeed;
	sf::Vector2f steeringForce = desiredVelocity - m_Velocity;
	Truncate(steeringForce, m_MaxForce);
	return steeringForce;
}

sf::Vector2f Agent::Flee(sf::Vector2f _targetPos)
{
	sf::Vector2f desiredVelocity = Normalize(GetPosition() - _targetPos) * m_MaxSpeed;
	sf::Vector2f steeringForce = desiredVelocity - m_Velocity;
	Truncate(steeringForce, m_MaxForce);
	return steeringForce;
}

sf::Vector2f Agent::Pursuit(Agent& _otherAgent)
{
	return Seek(_otherAgent.GetVelocity() + _otherAgent.GetPosition());
}

sf::Vector2f Agent::Evade(Agent& _otherAgent)
{
	return Flee(_otherAgent.GetVelocity() + _otherAgent.GetPosition());
}

sf::Vector2f Agent::Wander(float _wanderDistance, float _wanderRadius)
{
	
	float x = (Normalize(std::move(m_Velocity)).x * _wanderDistance) + cosf(ToRadians(m_WanderAngle)) * _wanderRadius;
	float y = (Normalize(std::move(m_Velocity)).y * _wanderDistance) + sinf(ToRadians(m_WanderAngle)) * _wanderRadius;

	srand(m_Velocity.x);

	sf::Vector2f steeringForce = Seek(sf::Vector2f{ x,y } + GetPosition());

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

	return steeringForce;
}

sf::Vector2f Agent::Seperation()
{
	sf::Vector2f steeringForce{ 0.0f, 0.0f };
	float numberOfAgents = 0.0f;
	for(auto& agent : *m_OtherAgents)
	{
		float distance = Mag(agent->GetPosition() - GetPosition());
		if (distance < m_NeighborhoodRadius / 2
			&& distance > 0)
		{
			sf::Vector2f diff = Normalize(GetPosition() - agent->GetPosition());
			diff /= distance;
			steeringForce += diff;
			numberOfAgents++;
		}
	}
	if (numberOfAgents > 0)
	{
		steeringForce /= numberOfAgents;
	}
	if (Mag(steeringForce) > 0)
	{
		steeringForce = Normalize(steeringForce) * m_MaxSpeed;
		steeringForce = (steeringForce - m_Velocity);
		Truncate(steeringForce, m_MaxForce);
	}
	return steeringForce;
}

sf::Vector2f Agent::Alignment()
{
	sf::Vector2f averageVelocity{ 0.0f, 0.0f };
	sf::Vector2f steeringForce{ 0.0f, 0.0f };
	float numberOfAgents = 0.0f;
	for (auto& agent : *m_OtherAgents)
	{
		float distance = Mag(agent->GetPosition() - GetPosition());
		if (distance > 0
			&& distance < m_NeighborhoodRadius)
		{
			averageVelocity += agent->GetVelocity();
			numberOfAgents++;
		}
	}
	if (numberOfAgents > 0)
	{
		averageVelocity /= numberOfAgents;
		averageVelocity = Normalize(averageVelocity) * m_MaxSpeed;
		steeringForce = averageVelocity - m_Velocity;
		Truncate(steeringForce, m_MaxForce);
	}
	return steeringForce;
}

sf::Vector2f Agent::Cohesion()
{
	sf::Vector2f centreOfMass{ 0.0f, 0.0f };
	sf::Vector2f steeringForce{ 0.0f, 0.0f };
	float numberOfAgents = 0.0f;
	for (auto& agent : *m_OtherAgents)
	{
		float distance = Mag(agent->GetPosition() - GetPosition());
		if (distance < m_NeighborhoodRadius
			&& distance > 0)
		{
			centreOfMass += agent->GetPosition();
			numberOfAgents++;
		}
	}
	if (numberOfAgents > 0)
	{
		centreOfMass /= numberOfAgents;
		steeringForce = Seek(centreOfMass);
	}
	return steeringForce;
}

sf::Vector2f Agent::Avoidence()
{
	float playerWidth = m_Sprite.getGlobalBounds().width / 2;
	float direction;
	sf::Vector2f steeringForce{ 0.0f,0.0f };
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
					steeringForce = CWPerp(m_Velocity);
					
				}
				// Obstacle On Left
				else
				{
					steeringForce = CCWPerp(m_Velocity);
				}
			}
		}
	}
	Truncate(steeringForce, m_MaxForce);
	return steeringForce;
}

sf::Vector2f Agent::LeaderFollowing()
{
	sf::Vector2f desiredPoint{ 0.0f, 0.0f };
	sf::Vector2f steeringForce{ 0.0f, 0.0f };
	for (auto& agent : *m_OtherAgents)
	{
		if (agent->IsLeader())
		{
			desiredPoint = Normalize(agent->GetInverseVelocity()) * m_LeaderFollowOffset;
			desiredPoint += agent->GetPosition();
			break;
		}
	}

	for (auto& agent : *m_OtherAgents)
	{
		if (agent->IsLeader())
		{
			if (Dot(Normalize(GetPosition() - agent->GetPosition()), Normalize(std::move(agent->GetVelocity()))) > 0
				&& Mag(agent->GetPosition() - GetPosition()) < m_NeighborhoodRadius)
			{
				steeringForce += Evade(*agent) * 5.0f;
				return steeringForce;
			}
		}
	}

	steeringForce += Seperation();

	steeringForce += Arrive(desiredPoint);

	return steeringForce;
}

sf::Vector2f Agent::Arrive(sf::Vector2f _location)
{
	sf::Vector2f steeringForce{ 0.0f, 0.0f };
	sf::Vector2f target_offset = _location - GetPosition();
	sf::Vector2f desiredVelocity{ 0.0f, 0.0f };
	float distance = Mag(target_offset);
	float rampedSpeed = m_MaxSpeed * (distance / m_SlowingRadius);
	float clippedSpeed = fmin(rampedSpeed, m_MaxSpeed);
	desiredVelocity = (clippedSpeed / distance) * target_offset;
	steeringForce = desiredVelocity - m_Velocity;

	return steeringForce;
}

Agent* Agent::GetNearestAgent()
{
	Agent* nearestAgent = nullptr; 
	for (auto& agent : *m_OtherAgents)
	{
		if (agent->GetID() != GetID())
		{
			nearestAgent = agent;
			break;
		}
	}
	for (auto& agent : *m_OtherAgents)
	{
		float distance = Mag(agent->GetPosition() - GetPosition());
		if(distance > 0)
		{
			if (Mag(nearestAgent->GetPosition() - GetPosition()) > distance)
				nearestAgent = agent;
		}
	}
	return nearestAgent;
}

