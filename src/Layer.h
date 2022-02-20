#ifndef LAYER_HPP
#define LAYER_HPP

#include "SFML/Graphics/Drawable.hpp"

#include "patogaem/robin_set.h"

class Layer
{
    public:

    Layer();
    ~Layer();

    void bindDrawable(sf::Drawable* drawable);
    void unbindDrawable(sf::Drawable* drawable);

    void clearDrawables();

    private:

    tsl::robin_set<sf::Drawable*> drawables;

};

//Backgroud (images), tilemap, sparse tile map, ...

#endif