#ifndef GENERIC__ENTITY_HPP
#define GENERIC__ENTITY_HPP

#include "Entity.hpp"

class GenericEntity : public Entity
{
    public:

    GenericEntity(Scene_Play* play, const sf::Vector2f& position, std::string name);
    ~GenericEntity();

    private:

};

#endif