#include "Obstacle.h"

Obstacle::Obstacle(std::string_view&& _textureAddress, sf::Vector2f&& _startPosition, sf::Vector2f&& _scale)
{
	m_SpriteTexture.loadFromFile(_textureAddress.data());
	m_Position = _startPosition;
	m_Scale = _scale;
	Start();
}

Obstacle::~Obstacle()
{
}

void Obstacle::Start()
{
	m_Sprite.setTexture(m_SpriteTexture, true);
	m_Sprite.setOrigin(m_Sprite.getGlobalBounds().width / 2, m_Sprite.getGlobalBounds().height / 2);
	m_Sprite.setPosition(m_Position);
	m_Sprite.setScale(m_Scale);
}

void Obstacle::Update()
{
}

sf::Vector2f Obstacle::GetPosition()
{
	return m_Sprite.getPosition();
}

sf::Vector2f Obstacle::GetSize()
{
	return {m_Sprite.getGlobalBounds().width,m_Sprite.getGlobalBounds().height};
}

sf::FloatRect Obstacle::GetGlobalBounds()
{
	return m_Sprite.getGlobalBounds();
}

void Obstacle::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Sprite, _states);
}