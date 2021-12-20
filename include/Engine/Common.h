#ifndef COMMON_H
#define COMMON_H

#include <functional>
#include <iostream>

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Drawable.hpp"

typedef std::function<void(const sf::Drawable&)> Renderer;


template<class T>
std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vector2)
{
    os << "(" << vector2.x << ", " << vector2.y << ")";
    return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const sf::Rect<T>& rect)
{
    os << "[" << rect.left << ", " << rect.top << " | " << rect.width << ", " << rect.height << "]";
    return os;
}

#endif