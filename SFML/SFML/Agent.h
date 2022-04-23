#pragma once
#include "Globals.h"
#include "Obstacle.h"

class Agent : public sf::Drawable, public sf::Transformable
{
public:
	Agent(float& _deltaTime, sf::Vector2i& _windowSize, sf::RenderWindow* _renderWindow, std::vector<Obstacle*>& _obstacleList, std::vector<Agent*>& _otherAgents);
	~Agent();
	void Start();
	void Update();
	void HandleInput();

	sf::Vector2f GetPosition();
	sf::Vector2f GetVelocity();
	void Translate(sf::Vector2f&& _translation);

	void SetState(char&& _state);
	void ToggleAvoidence();
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	void LoopWithScreen();
	void LookAt(sf::Vector2f&& _direction);

	void ApplySteeringForce();
	void Seek(sf::Vector2f _targetPos);
	void Flee(sf::Vector2f _targetPos);
	void Pursuit(Agent& _otherAgent);
	void Evade(Agent& _otherAgent);
	void Wander(float _wanderDistance, float _wanderRadius);
	int Seperation();
	void Avoidence();

	Agent* GetNearestAgent();

	sf::Sprite m_Sprite;
	sf::Texture m_SpriteTexture;
	sf::Vector2<float> m_Velocity{ 0.0f,0.0f };
	sf::Vector2f m_SteeringForce{};
	sf::RectangleShape m_CollisionRect{};
	sf::CircleShape m_NeighborCircle{};
	sf::Vector2<int>* m_WindowSize = nullptr;
	sf::RenderWindow* m_RenderWindow = nullptr;
	std::vector<Obstacle*>* m_Obsticles = nullptr;
	std::vector<Agent*>* m_OtherAgents = nullptr;
	float* m_DeltaTime = nullptr;

	float m_MaxSpeed = 200.0f;
	float m_MaxForce = 100.0f;
	float m_MaxAvoidenceForce = 100.0f;

	float m_WanderAngle = 0;
	bool m_WanderingLeft = true;

	float m_NeighborhoodRadius = 300.0f;

	bool m_IsSeeking = false;
	bool m_IsFleeing = false;
	bool m_IsPursuit = false;
	bool m_IsEvade = false;
	bool m_IsWander = false;
	bool m_IsSeperation = false;
	bool m_IsAvoidence = false;
	
};

