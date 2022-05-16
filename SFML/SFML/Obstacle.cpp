// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Obstacle.cpp 
// Description : Obstacle Implementation File
// Author : William Inman
// Mail : william.inman@mds.ac.nz

#include "Obstacle.h"

Obstacle::Obstacle(std::string_view&& _textureAddress, sf::Vector2f&& _startPosition, sf::Vector2f&& _scale)
{
	// Set sprite texture
	m_SpriteTexture.loadFromFile(_textureAddress.data());
	// Set position
	m_Position = _startPosition;
	// set scale
	m_Scale = _scale;
	Start();
}

Obstacle::~Obstacle()
{
}

void Obstacle::Start()
{
	m_Sprite.setTexture(m_SpriteTexture, true);
	m_Sprite.setScale(m_Scale);
	m_Sprite.setPosition(m_Position);
	SetOriginToCentre(m_Sprite);
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
