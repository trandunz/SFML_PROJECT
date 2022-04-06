#pragma once
#include "Globals.h"

class Agent : public sf::Drawable, public sf::Transformable
{
public:
	Agent(float& _deltaTime, sf::Vector2i& _windowSize, sf::RenderWindow* _renderWindow);
	~Agent();
	void Start();
	void Update();
	void HandleInput();

	void Translate(sf::Vector2f&& _translation);
	
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	void LookAt(sf::Vector2f&& _direction);

	void Seek(sf::Vector2f _targetPos);
	void Flee(sf::Vector2f _targetPos);

	sf::Sprite m_Sprite;
	sf::Texture m_SpriteTexture;
	sf::Vector2<float> m_Velocity{ 0.0f,0.0f };
	sf::Vector2<int>* m_WindowSize = nullptr;
	sf::RenderWindow* m_RenderWindow = nullptr;
	float* m_DeltaTime = nullptr;

	float m_MaxSpeed = 200.0f;
	float m_MaxForce = 100.0f;
};

