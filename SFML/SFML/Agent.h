// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Agent.h 
// Description : Agent Header File
// Author : William Inman
// Mail : william.inman@mds.ac.nz

#pragma once
#include "Globals.h"
#include "Obstacle.h"

class Agent : public sf::Drawable
{
public:
	/// <summary>
	/// Agent Constructor
	/// </summary>
	/// <param name="_initialPosition"></param>
	/// <param name="_deltaTime"></param>
	/// <param name="_windowSize"></param>
	/// <param name="_renderWindow"></param>
	/// <param name="_obstacleList"></param>
	/// <param name="_otherAgents"></param>
	Agent(sf::Vector2i _initialPosition, float& _deltaTime, sf::Vector2i& _windowSize, sf::RenderWindow* _renderWindow, std::vector<Obstacle*>& _obstacleList, std::vector<Agent*>& _otherAgents);
	
	/// <summary>
	/// Agent Destructor
	/// </summary>
	~Agent();

	/// <summary>
	/// Agent Start, Gets Called On Contruction
	/// </summary>
	void Start();

	/// <summary>
	/// Agent update, Handles frame-by-frame functionality
	/// </summary>
	void Update();

	/// <summary>
	/// Toggles Debug View For The Agent
	/// </summary>
	void ToggleDebugLines();

	/// <summary>
	/// Sets Debug View For Agent
	/// </summary>
	/// <param name="_isDebug"></param>
	void SetDebugLines(bool _isDebug);

	/// <summary>
	/// Returns bool corresponding to debug view status
	/// </summary>
	/// <returns></returns>
	bool IsDebug();

	/// <summary>
	/// Returns the agents global bounds
	/// </summary>
	/// <returns></returns>
	sf::FloatRect GetGlobalBounds();

	/// <summary>
	/// Returns the agents position
	/// </summary>
	/// <returns></returns>
	sf::Vector2f GetPosition();
	/// <summary>
	/// Returns the agents velocity
	/// </summary>
	/// <returns></returns>
	sf::Vector2f GetVelocity();
	/// <summary>
	/// Returns the inverse velocity of the agent
	/// </summary>
	/// <returns></returns>
	sf::Vector2f GetInverseVelocity();

	/// <summary>
	/// Returns the agents collision rectangle
	/// </summary>
	/// <returns></returns>
	sf::RectangleShape GetCollisionRect();

	/// <summary>
	/// Returns the agents current assigned ID
	/// </summary>
	/// <returns></returns>
	int GetID();

	/// <summary>
	/// Sets the agents ID
	/// </summary>
	/// <param name="_newID"></param>
	void SetID(int _newID);

	/// <summary>
	/// Translates the agent by specified amount
	/// </summary>
	/// <param name="_translation"></param>
	void Translate(sf::Vector2f&& _translation);

	/// <summary>
	/// Sets the behavior state of the agent.
	/// </summary>
	/// <param name="_state"></param>
	void SetState(char&& _state);

	/// <summary>
	/// Returns the agents current behavior state ID
	/// </summary>
	/// <returns></returns>
	char GetState();

	/// <summary>
	/// Toggles obstacle avoidence
	/// </summary>
	void ToggleAvoidence();

	/// <summary>
	/// Sets obstacle avoidence
	/// </summary>
	/// <param name="_isAvoidence"></param>
	void SetAvoidence(bool _isAvoidence);

	/// <summary>
	/// Returns true if agent is avoiding obstacles
	/// </summary>
	/// <returns></returns>
	bool IsAvoiding();

	/// <summary>
	/// Returns true if the agent is the leader
	/// </summary>
	/// <returns></returns>
	bool IsLeader();

	/// <summary>
	/// Toggles the agent as leader
	/// </summary>
	void ToggleLeader();

	/// <summary>
	/// Sets the agent as leader
	/// </summary>
	/// <param name="_isLeader"></param>
	void SetLeader(bool&& _isLeader);

private:

	/// <summary>
	/// Draws the agent to the screen along side debug lines if active.
	/// </summary>
	/// <param name="_target"></param>
	/// <param name="_states"></param>
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	/// <summary>
	/// Prevents the agent from leaving the screen
	/// </summary>
	void LoopWithScreen();

	/// <summary>
	/// Rotates the agent towards a direction
	/// </summary>
	/// <param name="_direction"></param>
	void LookAt(sf::Vector2f&& _direction);

	/// <summary>
	/// Applies a force to the agent
	/// </summary>
	/// <param name="_force"></param>
	void ApplyForce(sf::Vector2f _force);

	/// <summary>
	/// Handles seek behavior.
	/// returns steering force.
	/// </summary>
	/// <param name="_targetPos"></param>
	/// <returns></returns>
	sf::Vector2f Seek(sf::Vector2f _targetPos);

	/// <summary>
	/// Handles flee behavior.
	/// returns steering force.
	/// </summary>
	/// <param name="_targetPos"></param>
	/// <returns></returns>
	sf::Vector2f Flee(sf::Vector2f _targetPos);

	/// <summary>
	/// Handles Pursuit Behavior.
	/// returns steering force.
	/// </summary>
	/// <param name="_otherAgent"></param>
	/// <returns></returns>
	sf::Vector2f Pursuit(Agent& _otherAgent);
	/// <summary>
	/// Handles evade behavior
	/// returns steering force.
	/// </summary>
	/// <param name="_otherAgent"></param>
	/// <returns></returns>
	sf::Vector2f Evade(Agent& _otherAgent);
	/// <summary>
	/// Handles wander behavior.
	/// returns steering force.
	/// </summary>
	/// <param name="_wanderDistance"></param>
	/// <param name="_wanderRadius"></param>
	/// <returns></returns>
	sf::Vector2f Wander(float _wanderDistance, float _wanderRadius);
	/// <summary>
	/// Handles seperation behavior.
	/// returns steering force.
	/// </summary>
	/// <returns></returns>
	sf::Vector2f Seperation();
	/// <summary>
	/// Handles alignment behavior.
	/// returns steering force.
	/// </summary>
	/// <returns></returns>
	sf::Vector2f Alignment();
	/// <summary>
	/// Handles cohesion behavior.
	/// returns steering force.
	/// </summary>
	/// <returns></returns>
	sf::Vector2f Cohesion();
	/// <summary>
	/// Handles avoidence behavior.
	/// returns steering force.
	/// </summary>
	/// <returns></returns>
	sf::Vector2f Avoidence();
	/// <summary>
	/// handles leader following behavior.
	/// returns steering force.
	/// </summary>
	/// <returns></returns>
	sf::Vector2f LeaderFollowing();
	/// <summary>
	/// Handles arrive behavior.
	/// returns steering force.
	/// </summary>
	/// <param name="_location"></param>
	/// <returns></returns>
	sf::Vector2f Arrive(sf::Vector2f _location);

	/// <summary>
	/// Returns the nearest agent.
	/// </summary>
	/// <returns></returns>
	Agent* GetNearestAgent();

	sf::CircleShape m_Sprite{15,3};
	sf::Vector2<float> m_Velocity{ 0.0f,0.0f };
	sf::Vector2f m_Acceleration{ 0.0f,0.0f };
	sf::RectangleShape m_CollisionRect{};
	sf::CircleShape m_NeighborCircle{};
	sf::Vector2<int>* m_WindowSize = nullptr;
	sf::RenderWindow* m_RenderWindow = nullptr;
	std::vector<Obstacle*>* m_Obsticles = nullptr;
	std::vector<Agent*>* m_OtherAgents = nullptr;

	int m_AgentID = 0;

	float* m_DeltaTime = nullptr;

	float m_MaxSpeed = 200.0f;
	float m_MaxForce = 100.0f;
	float m_MaxAvoidenceForce = 100.0f;

	float m_WanderAngle = 0;
	bool m_WanderingLeft = true;
	bool m_DebugLines = false;
	bool m_IsLeader = false;

	float m_NeighborhoodRadius = 100.0f;
	float m_LeaderFollowOffset = 100.0f;
	float m_SlowingRadius = m_NeighborhoodRadius * 2;

	bool m_IsSeeking = false;
	bool m_IsFleeing = false;
	bool m_IsPursuit = false;
	bool m_IsEvade = false;
	bool m_IsWander = false;
	bool m_IsSeperation = false;
	bool m_IsAvoidence = false;
	bool m_IsAlignment = false;
	bool m_IsCohesion = false;
	bool m_IsFlocking = false;
	bool m_IsArriving = false;
	bool m_LeaderFollowing = false;
};

