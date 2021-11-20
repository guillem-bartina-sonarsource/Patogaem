
#include "TestPE.hpp"

#include "Engine/Resources.h"

TestPE::TestPE(Scene_Play* play, const sf::Vector2f& position, std::string name, b2BodyType type, CollisionCategory category, sf::Vector2f size) : PhysicEntity(play, position)
{
    setSprite(*Resources::getInstance()->Texture(name), sf::IntRect(ZEROVECTOR_I, sf::Vector2i(CELLSIZE)));

    setBody(type, true);
    addFixture(createRectangle(tob2Vec2(size)), category, 0.2f, 0.f, 1.f);
}

TestPE::~TestPE() {}

void TestPE::onCollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact)
{
    //printInfo("COLLIDED: " << getID() << " - " << collided->getID());
}