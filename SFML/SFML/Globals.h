#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <functional>
#include <cmath>

#define PI 3.14159265358979323846264338

static void Print(std::string_view&& _message)
{
	std::cout << _message << std::endl;
}
static void Print(int&& _int)
{
	std::cout << _int << std::endl;
}
static void Print(float&& _float)
{
	std::cout << _float << std::endl;
}
static void Print(char&& _character)
{
	std::cout << _character << std::endl;
}
static void Print(sf::Vector2f&& _vector)
{
	std::cout << "X: " << _vector.x << "Y: " << _vector.y << std::endl;
}
static float Mag(sf::Vector2f&& _vector)
{
	return sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y));
}
static float Mag(const sf::Vector2f& _vector)
{
	return sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y));
}
static sf::Vector2f Normalize(sf::Vector2f&& _vector)
{
	return _vector / Mag(_vector);
}
static sf::Vector2f Normalize(const sf::Vector2f& _vector)
{
	return _vector / Mag(_vector);
}
static void Truncate(sf::Vector2f& _vector, float _upperBound)
{
	float i = _upperBound / Mag(_vector);
	i = i < 1 ? i : 1;
	_vector *= i;
}
static sf::Vector2f Truncate(sf::Vector2f&& _vector, float _upperBound)
{
	sf::Vector2f truncated = _vector;
	float i = _upperBound / Mag(truncated);
	i = i < 1 ? i : 1;
	truncated *= i;
	return truncated;
}
static void Limit(sf::Vector2f& _vector, float _value)
{
	float i = _value / Mag(_vector);
	_vector *= i;
}
static float Dot(sf::Vector2f&& _v1, sf::Vector2f&& _v2)
{
	float product = 0.0f;
	product += _v1.x * _v2.x;
	product += _v1.y * _v2.y;
	return product;
}
static void SetOriginToCentre(sf::Shape& _object)
{
	_object.setOrigin(_object.getGlobalBounds().width / 2, _object.getGlobalBounds().height / 2);
}
static void SetOriginToCentre(sf::Sprite& _sprite)
{
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
}
static float ToDegrees(float _radians)
{
	return _radians * (180.0f / (float)PI);
}
static float ToRadians(float _degrees)
{
	return ((float)PI * _degrees) / 180.0f;
}
static sf::Vector2f CWPerp(sf::Vector2f _originalVector)
{
	return { _originalVector.y, -_originalVector.x };
}
static sf::Vector2f CCWPerp(sf::Vector2f _originalVector)
{
	return { -_originalVector.y, _originalVector.x };
}
static float AngleDir(sf::Vector2f _A, sf::Vector2f _B)
{
	return -_A.x * _B.y + _A.y * _B.x;
}

