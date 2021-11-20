#ifndef GENERIC__PHYSIC__ENTITY_HPP
#define GENERIC__PHYSIC__ENTITY_HPP

#include "PhysicEntity.hpp"

class GenericPhysicEntity : public PhysicEntity
{
    public:

    GenericPhysicEntity(Scene_Play* play, const sf::Vector2f& position, std::string name);
    ~GenericPhysicEntity();

    private:

};

#endif