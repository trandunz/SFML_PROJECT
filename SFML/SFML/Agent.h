#pragma once
#include "Globals.h"

class Agent : public sf::Drawable, public sf::Transformable
{
public:
	Agent();
	~Agent();
	void Start();
	void Update();
	void HandleInput();

	void Translate(sf::Vector2f&& _translation);
	
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	sf::Sprite m_Sprite;
	sf::Texture m_SpriteTexture;
	sf::Vector2<float> m_Velocity{ 0.0f,0.0f };
	float m_MaxSpeed = 100.0f;
};

