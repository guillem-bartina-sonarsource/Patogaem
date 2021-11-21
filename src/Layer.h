#ifndef LAYER_HPP
#define LAYER_HPP

#include "EntityCollection.h"

class Layer
{
    public:

    Layer();
    ~Layer();

    private:

    EntityCollection* entities;

};

#endif