#ifndef COMMON_H
#define COMMON_H

#include <functional>

#include "SFML/Graphics/Drawable.hpp"

typedef std::function<void(const sf::Drawable&)> Renderer;

#endif