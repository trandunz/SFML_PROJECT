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
