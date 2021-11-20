
#include "GenericPhysicEntity.hpp"

#include "Engine/Resources.h"
#include "Utils.hpp"
#include "EntityCreator.hpp"

GenericPhysicEntity::GenericPhysicEntity(Scene_Play* play, const sf::Vector2f& position, std::string name) : PhysicEntity(play, position)
{
    setSprite(*Resources::getInstance()->Texture(name), sf::IntRect(ZEROVECTOR_I, sf::Vector2i(CELLSIZE)));

    sf::Vector2u rect = Resources::getInstance()->Texture(name)->getSize();

    if(rect.x > int(CELLSIZE.x))
    {
        animate(rect.x / int(CELLSIZE.x), sf::seconds(0.1f));
    }

    setBody(b2BodyType::b2_staticBody);
    addFixture(createRectangle(tob2Vec2(CELLSIZE)), CollisionCategory_STATIC_FOREGROUND, 0.f, 0.f, 1.f);

    setCODE(GENERICPHYSICENTITY);
}

GenericPhysicEntity::~GenericPhysicEntity() {}