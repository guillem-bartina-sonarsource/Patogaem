#include "Engine/DrawableSet.h"

DrawableSet::DrawableSet(const std::vector<sf::Drawable*>& drawables)
: drawables(drawables)
{}

DrawableSet::~DrawableSet()
{
    for(sf::Drawable*& drawable : drawables)
    {
        delete drawable;
    }
}

void DrawableSet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(sf::Drawable* const& drawable : drawables)
    {
        target.draw(*drawable, states);
    }
}