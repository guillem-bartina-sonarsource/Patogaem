
#include "Holdable.hpp"

Holdable::Holdable() {}

Holdable::Holdable(Scene_Play* play, const sf::Vector2f& position) : Object(play, position) {}

Holdable::Holdable(Scene_Play* play, const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& rect) : Object(play, position, texture, rect) {}

Holdable::~Holdable() {}

Holdable* Holdable::get()
{
    body->SetEnabled(false);
    return this;
}

Entity* Holdable::unget(const sf::Vector2f& impulse)
{
    body->SetEnabled(true);
    body->ApplyLinearImpulse(tob2Vec2(impulse * body->GetMass()), body->GetWorldCenter(), true);
    return this;
}