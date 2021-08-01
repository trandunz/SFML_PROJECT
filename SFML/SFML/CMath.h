#pragma once
#include <SFML/System.hpp>
class CMath
{
public:
	static const sf::Vector2f Normalize(sf::Vector2f _vector2);
	static const float Magnitude(sf::Vector2f _vector2);
	static const float Dot(sf::Vector2f, sf::Vector2f);
};

