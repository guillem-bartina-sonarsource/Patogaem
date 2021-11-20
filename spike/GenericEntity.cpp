
#include "GenericEntity.hpp"

#include "Engine/Resources.h"
#include "Utils.hpp"
#include "EntityCreator.hpp"

GenericEntity::GenericEntity(Scene_Play* play, const sf::Vector2f& position, std::string name) : Entity(play, position)
{
    setSprite(*Resources::getInstance()->Texture(name), sf::IntRect(ZEROVECTOR_I, sf::Vector2i(CELLSIZE)));

    sf::Vector2u rect = Resources::getInstance()->Texture(name)->getSize();

    if(rect.x > int(CELLSIZE.x))
    {
        animate(rect.x / int(CELLSIZE.x), sf::seconds(0.1f));
    }

    setCODE(GENERICENTITY);
}

GenericEntity::~GenericEntity() {}