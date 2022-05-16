// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Globals.h 
// Description : Globals Functions, Includes
//					And Pre-Proccessor Values
// Author : William Inman
// Mail : william.inman@mds.ac.nz

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <functional>
#include <cmath>

#define PI 3.14159265358979323846264338

/// <summary>
/// Prints specified message
/// </summary>
/// <param name="_message"></param>
static void Print(std::string_view&& _message)
{
	std::cout << _message << std::endl;
}
/// <summary>
/// Prints specified int
/// </summary>
/// <param name="_int"></param>
static void Print(int&& _int)
{
	std::cout << _int << std::endl;
}
/// <summary>
/// Prints specified float
/// </summary>
/// <param name="_float"></param>
static void Print(float&& _float)
{
	std::cout << _float << std::endl;
}
/// <summary>
/// Prints specified character
/// </summary>
/// <param name="_character"></param>
static void Print(char&& _character)
{
	std::cout << _character << std::endl;
}
/// <summary>
/// Prints specified vector
/// </summary>
/// <param name="_vector"></param>
static void Print(sf::Vector2f&& _vector)
{
	std::cout << "X: " << _vector.x << "Y: " << _vector.y << std::endl;
}
/// <summary>
/// Returns the magnitude of the vector
/// </summary>
/// <param name="_vector"></param>
/// <returns></returns>
static float Mag(sf::Vector2f&& _vector)
{
	return sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y));
}
/// <summary>
/// Returns the magnituse of the vector
/// </summary>
/// <param name="_vector"></param>
/// <returns></returns>
static float Mag(const sf::Vector2f& _vector)
{
	return sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y));
}
/// <summary>
/// returns the vector normalized
/// </summary>
/// <param name="_vector"></param>
/// <returns></returns>
static sf::Vector2f Normalize(sf::Vector2f&& _vector)
{
	if (Mag(_vector) <= 0)
		return { 0.0f,0.0f };

	return _vector / Mag(_vector);
}
/// <summary>
/// Returns the vector normalized
/// </summary>
/// <param name="_vector"></param>
/// <returns></returns>
static sf::Vector2f Normalize(const sf::Vector2f& _vector)
{
	if (Mag(_vector) <= 0)
		return { 0.0f,0.0f };
	return _vector / Mag(_vector);
}
/// <summary>
/// Truncates the specified vector to the specified upperbound
/// </summary>
/// <param name="_vector"></param>
/// <param name="_upperBound"></param>
static void Truncate(sf::Vector2f& _vector, float _upperBound)
{
	if (Mag(_vector) > 0)
	{
		float i = _upperBound / Mag(_vector);
		i = i < 1 ? i : 1;
		_vector *= i;
	}
}
/// <summary>
/// Returns the truncated value value of the specified vector
/// </summary>
/// <param name="_vector"></param>
/// <param name="_upperBound"></param>
/// <returns></returns>
static sf::Vector2f Truncate(sf::Vector2f&& _vector, float _upperBound)
{
	sf::Vector2f truncated = _vector;
	float i = _upperBound / Mag(truncated);
	i = i < 1 ? i : 1;
	truncated *= i;
	return truncated;
}
/// <summary>
/// Sets the specified vectors magnitude to the value
/// </summary>
/// <param name="_vector"></param>
/// <param name="_value"></param>
static void Limit(sf::Vector2f& _vector, float _value)
{
	float i = _value / Mag(_vector);
	_vector *= i;
}
/// <summary>
/// Returns the dot product between the two vectors
/// </summary>
/// <param name="_v1"></param>
/// <param name="_v2"></param>
/// <returns></returns>
static float Dot(sf::Vector2f&& _v1, sf::Vector2f&& _v2)
{
	float product = 0.0f;
	product += _v1.x * _v2.x;
	product += _v1.y * _v2.y;
	return product;
}
/// <summary>
/// Sets the origin of the shape to its centre.
/// </summary>
/// <param name="_object"></param>
static void SetOriginToCentre(sf::Shape& _object)
{
	_object.setOrigin(_object.getGlobalBounds().width / 2, _object.getGlobalBounds().height / 2);
}
/// <summary>
/// Sets the origin of the sprite to its centre
/// </summary>
/// <param name="_sprite"></param>
static void SetOriginToCentre(sf::Sprite& _sprite)
{
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
}
/// <summary>
/// Sets the origin of the text to its centre
/// </summary>
/// <param name="_text"></param>
static void SetOriginToCentre(sf::Text& _text)
{
	_text.setOrigin(_text.getGlobalBounds().width / 2, _text.getGlobalBounds().height / 2);
}
/// <summary>
/// Returns the specified radians value in degrees
/// </summary>
/// <param name="_radians"></param>
/// <returns></returns>
static float ToDegrees(float _radians)
{
	return _radians * (180.0f / (float)PI);
}
/// <summary>
/// Returns the specified degrees value in radians
/// </summary>
/// <param name="_degrees"></param>
/// <returns></returns>
static float ToRadians(float _degrees)
{
	return ((float)PI * _degrees) / 180.0f;
}
/// <summary>
/// Gets the Clock-wise perpandicular vector
/// </summary>
/// <param name="_originalVector"></param>
/// <returns></returns>
static sf::Vector2f CWPerp(sf::Vector2f _originalVector)
{
	return { _originalVector.y, -_originalVector.x };
}
/// <summary>
/// Gets the counter-Clockwise perpandicular vector
/// </summary>
/// <param name="_originalVector"></param>
/// <returns></returns>
static sf::Vector2f CCWPerp(sf::Vector2f _originalVector)
{
	return { -_originalVector.y, _originalVector.x };
}
/// <summary>
/// returns the angle direction between vector a and vector b
/// </summary>
/// <param name="_A"></param>
/// <param name="_B"></param>
/// <returns></returns>
static float AngleDir(sf::Vector2f _a, sf::Vector2f _b)
{
	return -_a.x * _b.y + _a.y * _b.x;
}

