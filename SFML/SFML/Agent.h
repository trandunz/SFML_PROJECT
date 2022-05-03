#pragma once
#include "Globals.h"
#include "Obstacle.h"

class Agent : public sf::Drawable
{
public:
	Agent(sf::Vector2i _initialPosition, float& _deltaTime, sf::Vector2i& _windowSize, sf::RenderWindow* _renderWindow, std::vector<Obstacle*>& _obstacleList, std::vector<Agent*>& _otherAgents);
	~Agent();
	void Start();
	void Update();
	void HandleInput();

	void ToggleDebugLines();

	sf::FloatRect GetGlobalBounds();
	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();
	sf::Vector2f GetInverseVelocity();
	sf::RectangleShape GetCollisionRect();
	int GetID();
	void SetID(int _newID);
	void Translate(sf::Vector2f&& _translation);
	void SetState(char&& _state);
	char GetState();
	void ToggleAvoidence();
	void SetAvoidence(bool _isAvoidence);
	bool IsAvoiding();
	bool IsLeader();
	void ToggleLeader();
	void SetLeader(bool&& _isLeader);

	bool IsWandering();
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	void LoopWithScreen();
	void LookAt(sf::Vector2f&& _direction);

	void ApplyForce(sf::Vector2f _force);
	sf::Vector2f Seek(sf::Vector2f _targetPos);
	sf::Vector2f Flee(sf::Vector2f _targetPos);
	sf::Vector2f Pursuit(Agent& _otherAgent);
	sf::Vector2f Evade(Agent& _otherAgent);
	sf::Vector2f Wander(float _wanderDistance, float _wanderRadius);
	sf::Vector2f Seperation();
	sf::Vector2f Alignment();
	sf::Vector2f Cohesion();
	sf::Vector2f Avoidence();
	sf::Vector2f LeaderFollowing();
	sf::Vector2f Arrive(sf::Vector2f _location);

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

