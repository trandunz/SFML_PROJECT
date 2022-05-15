// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Obstacle.h 
// Description : Obstacle Header File
// Author : William Inman
// Mail : william.inman@mds.ac.nz

#pragma once
#include "Globals.h"
class Obstacle : public sf::Drawable
{
public:
	/// <summary>
	/// Obstacle Contructor
	/// </summary>
	/// <param name="_textureAddress"></param>
	/// <param name="_startPosition"></param>
	/// <param name="_scale"></param>
	Obstacle(std::string_view&& _textureAddress, sf::Vector2f&& _startPosition, sf::Vector2f&& _scale);
	
	/// <summary>
	/// Obstacle Destructor
	/// </summary>
	~Obstacle();

	/// <summary>
	/// Obstacle Start, Gets Called On Contruction
	/// </summary>
	void Start();

	/// <summary>
	/// Returns the position of the obstacle
	/// </summary>
	/// <returns></returns>
	sf::Vector2f GetPosition();

	/// <summary>
	/// Returns the size of the obstacle
	/// </summary>
	/// <returns></returns>
	sf::Vector2f GetSize();

	/// <summary>
	/// Returns the global bounds of the obstacle
	/// </summary>
	/// <returns></returns>
	sf::FloatRect GetGlobalBounds();
private:

	/// <summary>
	/// Draws the obstacle to the screen
	/// </summary>
	/// <param name="_target"></param>
	/// <param name="_states"></param>
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	sf::Sprite m_Sprite;
	sf::Texture m_SpriteTexture;
	sf::Vector2f m_Position{0,0};
	sf::Vector2f m_Scale{ 1,1 };
};

