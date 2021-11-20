#ifndef TEST__PE_HPP
#define TEST__PE_HPP

#include "PhysicEntity.hpp"

#include "Utils.hpp"

class TestPE : public PhysicEntity
{
    public:

    TestPE(Scene_Play* play, const sf::Vector2f& position, std::string name, b2BodyType type, CollisionCategory category, sf::Vector2f size = CELLSIZE);
    ~TestPE();

    virtual void onCollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact) override;

    private:

};

#endif