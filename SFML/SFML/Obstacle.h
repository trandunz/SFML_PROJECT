#pragma once
#include "Globals.h"
class Obstacle : public sf::Drawable, public sf::Transformable
{
public:
	Obstacle(std::string_view&& _textureAddress, sf::Vector2f&& _startPosition, sf::Vector2f&& _scale);
	~Obstacle();

	void Start();
	void Update();

	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
	sf::FloatRect GetGlobalBounds();
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	sf::Sprite m_Sprite;
	sf::Texture m_SpriteTexture;
	sf::Vector2f m_Position{0,0};
	sf::Vector2f m_Scale{ 1,1 };
};

