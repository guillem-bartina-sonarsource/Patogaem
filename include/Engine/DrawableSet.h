#ifndef DRAWABLESET_H
#define DRAWABLESET_H

#include <vector>

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Drawable.hpp"

class DrawableSet : public sf::Drawable
{
    public:

    DrawableSet(const std::vector<sf::Drawable*>& drawables);
    ~DrawableSet();

    private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::vector<Drawable*> drawables;

};

#endif