
#include "Crate.hpp"

#include "Engine/Resources.h"
#include "Utils.hpp"
#include "EntityCreator.hpp"

Crate::Crate(Scene_Play* play, const sf::Vector2f& position) : Holdable(play, position)
{
    setSprite(*Resources::getInstance()->Texture("textures/crate.png"), sf::IntRect(ZEROVECTOR_I, sf::Vector2i(CELLSIZE)));
    
    addBody(b2BodyType::b2_dynamicBody, true);
    addFixture(createRectangle(tob2Vec2(sf::Vector2f(CELLSIZE.x-4, CELLSIZE.y-4))), CollisionCategory_DYNAMIC_FOREGROUND, 0.5f, 0.f, 1.f);

    //b2EdgeShape* es = new b2EdgeShape(createEdge(b2Vec2((-CELLSIZE.x/2.f)+1, (-CELLSIZE.y/2.f)+1), b2Vec2((CELLSIZE.x/2.f)-1, (-CELLSIZE.y/2.f)+1)));
    //addFixture(es, CollisionCategory_DYNAMIC_FOREGROUND, 0.f, 0.f, 0.f);

    setCODE(CRATE);
}

Crate::~Crate() {}