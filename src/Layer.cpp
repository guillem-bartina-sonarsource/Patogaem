
#include "Layer.h"

Layer::Layer() {}

Layer::~Layer() {}

void Layer::bindDrawable(sf::Drawable* drawable)
{
    drawables.insert(drawable);
}

void Layer::unbindDrawable(sf::Drawable* drawable)
{
    drawables.erase(drawable);
}

void Layer::clearDrawables()
{
    drawables.clear();
}