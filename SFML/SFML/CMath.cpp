#include "CMath.h"
#include <iostream>

const sf::Vector2f CMath::Normalize(sf::Vector2f _vector2)
{
    return _vector2/ Magnitude(_vector2);
}

const float CMath::Magnitude(sf::Vector2f _vector2)
{
    float Mag = sqrt(((_vector2.x) * (_vector2.x)) + ((_vector2.y) * (_vector2.y)));
    return Mag;
}

const float CMath::Dot(sf::Vector2f _vector1, sf::Vector2f _vector2)
{
    float product = 0;

    // Loop for calculate cot product
    for (int i = 0; i < 2; i++)

        product = product + _vector1.x * _vector2.x;

    return product;
}
