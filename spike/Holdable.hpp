#ifndef HOLDABLE_HPP
#define HOLDABLE_HPP

#include "Object.hpp"

class Holdable : public Object
{
    public:

    Holdable();
    Holdable(Scene_Play* play, const sf::Vector2f& position);
    Holdable(Scene_Play* play, const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& rect);
    ~Holdable();

    Holdable* get();
    Entity* unget(const sf::Vector2f& impulse);

    protected:

    private:

};

#endif