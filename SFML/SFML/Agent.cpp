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
	// Free up pointers
	m_WindowSize = nullptr;
	m_DeltaTime = nullptr;
	m_RenderWindow = nullptr;
	m_Obsticles = nullptr;
	m_OtherAgents = nullptr;
}

void Agent::Start()
{
	SetOriginToCentre(m_Sprite);

	// Start velocity with -max speed in y direction
	m_Velocity = {0, -m_MaxSpeed};
	// Set origin of collision rectangle to middle of width
	m_CollisionRect.setOrigin({ m_Sprite.getLocalBounds().width / 2, 0 });
	m_CollisionRect.setFillColor(sf::Color::Transparent);
	m_CollisionRect.setOutlineColor(sf::Color::Cyan);
	m_CollisionRect.setOutlineThickness(1);

	m_NeighborCircle.setFillColor(sf::Color::Transparent);
	m_NeighborCircle.setOutlineColor(sf::Color::Green);
	m_NeighborCircle.setOutlineThickness(1);
	// Make smooth circle
	m_NeighborCircle.setPointCount(360);
	// Sett radius to neighbourhood
	m_NeighborCircle.setRadius(m_NeighborhoodRadius);

	SetOriginToCentre(m_NeighborCircle);
}

void Agent::Update()
{
	// Get mouse pos
	sf::Vector2f mousepos = (sf::Vector2f)sf::Mouse::getPosition(*m_RenderWindow);

	// Make null steering force
	sf::Vector2f steeringForce{ 0.0f,0.0f };
	m_Acceleration = { 0.0f,0.0f };
	
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
		if (m_IsLeader)
		{
			// Seek if the agent is leader
			steeringForce += Seek((sf::Vector2f)sf::Mouse::getPosition(*m_RenderWindow));
		}
		else
		{
			// Evade is not leader
			for (auto& agent : *m_OtherAgents)
			{
				if (agent->IsLeader())
				{
					steeringForce += Evade(*agent);
					break;
				}
			}
		}
	}
	if (m_IsPursuit)
	{
		if (m_IsLeader)
		{
			// Seek if agent is leader
			steeringForce += Seek((sf::Vector2f)sf::Mouse::getPosition(*m_RenderWindow));
		}
		else
		{
			// Pursuit if agent is not leader
			for (auto& agent : *m_OtherAgents)
			{
				if (agent->IsLeader())
				{
					steeringForce += Pursuit(*agent);
					break;
				}
			}
		}
	}
	if (m_IsSeeking)
	{
		steeringForce += Seek(mousepos);
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
		// Seek if is leader else follow leader
		if (m_IsLeader)
			steeringForce += Seek((sf::Vector2f)sf::Mouse::getPosition(*m_RenderWindow));
		else
			steeringForce += LeaderFollowing();
	}
	// if steering forces are not present, wander
	if (Mag(steeringForce) <= 0)
	{
		steeringForce += Wander(100, 20);
	}
	// Avoid obsticles
	if (m_IsAvoidence)
	{
		steeringForce += Avoidence() * 5.0f;
	}
	
	// Apply the steering force to m_Acceleration
	ApplyForce(steeringForce);
	// Change velocity based on m_Acceleration with respect to delta time
	m_Velocity += m_Acceleration * (*m_DeltaTime);
	// Prevents velocity going past max speed
	Truncate(m_Velocity, m_MaxSpeed);
	// Translates the mesh with some velocity
	Translate(m_Velocity * (*m_DeltaTime));
	// Look at the velocity vector (always point forward)
	LookAt(std::move(m_Velocity));
	// Make sure the agent loops with the screen size
	LoopWithScreen();

	// Scale the collision rectangle with velocity * 1.5f in y and mesh width with small error margin
	m_CollisionRect.setSize({ m_Sprite.getLocalBounds().width * 1.2f, -Mag(m_Velocity) * 1.5f });
	// Update its position and rotation to match agent
	m_CollisionRect.setPosition(GetPosition());
	m_CollisionRect.setRotation(m_Sprite.getRotation());
	
	// If debug then update neighborhood circle position 
	// Neighborhood circle position is only used for showing neighborhood radius
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
	// Set all behaviors to false
	m_IsFleeing = false;
	m_IsSeeking = false;
	m_IsPursuit = false;
	m_IsEvade = false;
	m_IsWander = false;
	m_IsSeperation = false;
	m_IsAlignment = false;
	m_IsCohesion = false;
	m_IsFlocking = false;
	m_LeaderFollowing = false;

	// Set new state
	switch (_state)
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
	// return state id based on active state
	// return '!' if error
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
	// Set all other agents to not be leader
	for (auto& agent : *m_OtherAgents)
	{
		agent->SetLeader(false);
	}
	// Set this agent to be leader
	m_IsLeader = true;

	// Update mesh color based on leadership
	m_Sprite.setFillColor(sf::Color::Red);
}

void Agent::SetLeader(bool&& _isLeader)
{
	m_IsLeader = _isLeader;

	// Update mesh color based on leadership
	if (m_IsLeader)
		m_Sprite.setFillColor(sf::Color::Red);
	else
		m_Sprite.setFillColor(sf::Color::White);
}

void Agent::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	// Draw the mesh
	_target.draw(m_Sprite, _states);

	// Draw all debug meshes 
	if (m_DebugLines)
	{
		_target.draw(m_NeighborCircle, _states);

		_target.draw(m_CollisionRect, _states);

		// create new vertex array for velocity, set it white and draw it
		sf::VertexArray velocity(sf::LinesStrip, 2);
		velocity[0].position = m_Sprite.getPosition();
		velocity[0].color = sf::Color::White;
		velocity[1].position = m_Sprite.getPosition() + m_Velocity;
		velocity[1].color = sf::Color::White;
		_target.draw(velocity, _states);

		// create new vertex array for steeringforce, set it red and draw it
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
	// Get desired velocity
	sf::Vector2f desiredVelocity = Normalize(_targetPos - GetPosition()) * m_MaxSpeed;
	// Apply it to steering force
	sf::Vector2f steeringForce = desiredVelocity - m_Velocity;
	Truncate(steeringForce, m_MaxForce);
	return steeringForce;
}

sf::Vector2f Agent::Flee(sf::Vector2f _targetPos)
{
	// Get desired velocity
	sf::Vector2f desiredVelocity = Normalize(GetPosition() - _targetPos) * m_MaxSpeed;
	// Apply it to steering force
	sf::Vector2f steeringForce = desiredVelocity - m_Velocity;
	Truncate(steeringForce, m_MaxForce);
	return steeringForce;
}

sf::Vector2f Agent::Pursuit(Agent& _otherAgent)
{
	// Get future position and seek to it (timeToArrive = d/v)
	sf::Vector2f future = _otherAgent.GetPosition();
	float timeToArrive = Mag(_otherAgent.GetPosition() - GetPosition()) / m_MaxSpeed;
	future += _otherAgent.GetVelocity() * timeToArrive;
	return Seek(future);
}

sf::Vector2f Agent::Evade(Agent& _otherAgent)
{
	// Get future position and flee it (timeToArrive = d/v)
	sf::Vector2f future = _otherAgent.GetPosition(); 
	float timeToArrive = Mag(_otherAgent.GetPosition() - GetPosition()) / m_MaxSpeed;
	future += _otherAgent.GetVelocity() * timeToArrive;
	return Flee(future);
}

sf::Vector2f Agent::Wander(float _wanderDistance, float _wanderRadius)
{
	// Get position on semi circle based on wander radius
	float x = (Normalize(std::move(m_Velocity)).x * _wanderDistance) + cosf(ToRadians(m_WanderAngle)) * _wanderRadius;
	float y = (Normalize(std::move(m_Velocity)).y * _wanderDistance) + sinf(ToRadians(m_WanderAngle)) * _wanderRadius;

	// Seek to position on semi circle
	sf::Vector2f steeringForce = Seek(sf::Vector2f{ x,y } + GetPosition());

	// Update semicircle position with random swaying speed
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

	// Loop over all agents
	for(auto& agent : *m_OtherAgents)
	{
		// Get the distance between the two agents
		float distance = Mag(agent->GetPosition() - GetPosition());
		// If the distance is less than the neighborhoodradius / 2
		if (distance < m_NeighborhoodRadius / 2
			&& distance > 0)
		{
			// get the direction from the other agent to the current
			sf::Vector2f diff = Normalize(GetPosition() - agent->GetPosition());
			// devide the direction by the distance
			diff /= distance;
			// add it too the steering force
			steeringForce += diff;
			// increase agent count
			numberOfAgents++;
		}
	}
	if (numberOfAgents > 0)
	{
		// get average of the added forces
		steeringForce /= numberOfAgents;
	}
	if (Mag(steeringForce) > 0)
	{
		// limit the steering force to the max speed
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
	// loop over all agents
	for (auto& agent : *m_OtherAgents)
	{
		// Get distance between the two
		float distance = Mag(agent->GetPosition() - GetPosition());
		// If distance is less than neighborhood radius
		if (distance > 0
			&& distance < m_NeighborhoodRadius)
		{
			// add agent velocity
			averageVelocity += agent->GetVelocity();
			// increment agent count
			numberOfAgents++;
		}
	}
	if (numberOfAgents > 0)
	{
		// get average velocity
		averageVelocity /= numberOfAgents;
		// limit it too the max speed
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
	// loop over all agents
	for (auto& agent : *m_OtherAgents)
	{
		// get distance
		float distance = Mag(agent->GetPosition() - GetPosition());
		// if distance is less than neighborhood radius
		if (distance < m_NeighborhoodRadius
			&& distance > 0)
		{
			// add positions together
			centreOfMass += agent->GetPosition();
			// increment agent count
			numberOfAgents++;
		}
	}
	if (numberOfAgents > 0)
	{
		// get average position / centre of mass
		centreOfMass /= numberOfAgents;
		// seek to centre of mass
		steeringForce = Seek(centreOfMass);
	}
	return steeringForce;
}

sf::Vector2f Agent::Avoidence()
{
	float direction;
	sf::Vector2f steeringForce{ 0.0f,0.0f };
	// 
	for (auto& obstacle : *m_Obsticles)
	{
		// if agent is inside object then just flee it :(
		float distance = Mag(obstacle->GetPosition() - GetPosition());
		if (distance < obstacle->GetSize().x / 2)
		{
			return Flee(obstacle->GetPosition());
		}

		// Is Obstacle In Front Of Enemy
		if (Dot(Normalize(obstacle->GetPosition() - GetPosition()), Normalize(std::move(m_Velocity))) > 0)
		{
			// Obstacle In Collision Box
			if (m_CollisionRect.getGlobalBounds().intersects(obstacle->GetGlobalBounds()))
			{
				// Get direction
				direction = AngleDir(Normalize(obstacle->GetPosition() - GetPosition()), Normalize(std::move(m_Velocity)));
				// Obstacle On Right
				if (direction >= 0)
				{
					// Apply force clockwise purpandicular to velocity
					steeringForce = CWPerp(m_Velocity);
					
				}
				// Obstacle On Left
				else
				{
					// Apply force Counter- clockwise purpandicular to velocity
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
	Agent* leaderAgent{ nullptr };
	// Find leader and get the position behind it as desired point
	for (auto& agent : *m_OtherAgents)
	{
		if (agent->IsLeader())
		{
			// Store leader agent for later use
			leaderAgent = agent;
			desiredPoint = Normalize(agent->GetInverseVelocity()) * m_LeaderFollowOffset;
			desiredPoint += agent->GetPosition();
			break;
		}
	}

	if (leaderAgent)
	{
		if (Dot(Normalize(GetPosition() - leaderAgent->GetPosition()), Normalize(std::move(leaderAgent->GetVelocity()))) > 0
			&& Mag(leaderAgent->GetPosition() - GetPosition()) < m_NeighborhoodRadius)
		{
			steeringForce += Evade(*leaderAgent) * 10.0f;
			return steeringForce;
		}
	}

	// else

	// apply seperation
	steeringForce += Seperation();

	// arrive at positiopn behind agent
	steeringForce += Arrive(desiredPoint);

	return steeringForce;
}

sf::Vector2f Agent::Arrive(sf::Vector2f _location)
{
	sf::Vector2f steeringForce{ 0.0f, 0.0f };
	// Get distance vector to location from agent
	sf::Vector2f targetOffset = _location - GetPosition();
	sf::Vector2f desiredVelocity{ 0.0f, 0.0f };
	float distance = Mag(targetOffset);
	if (distance > 0)
	{
		// ramp down speed based on distance / slowing radius
		float rampedSpeed = m_MaxSpeed * (distance / m_SlowingRadius);
		float clippedSpeed = fmin(rampedSpeed, m_MaxSpeed);
		// get desired velocity based on distance and newly calculated speed
		desiredVelocity = (clippedSpeed / distance) * targetOffset;
	}
	
	steeringForce = desiredVelocity - m_Velocity;

	return steeringForce;
}

Agent* Agent::GetNearestAgent()
{
	Agent* nearestAgent = nullptr; 
	// Initialize nearestAgent with any agent other than this agent
	for (auto& agent : *m_OtherAgents)
	{
		if (agent->GetID() != GetID())
		{
			nearestAgent = agent;
			break;
		}
	}

	// Get closest agent
	for (auto& agent : *m_OtherAgents)
	{
		float distance = Mag(agent->GetPosition() - GetPosition());
		if(distance > 0)
		{
			if (Mag(nearestAgent->GetPosition() - GetPosition()) > distance)
				nearestAgent = agent;
		}
	}

	// Returns it
	return nearestAgent;
}

