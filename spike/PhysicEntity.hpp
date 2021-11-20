#ifndef PHYSIC_ENTITY_HPP
#define PHYSIC_ENTITY_HPP

#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_world.h"

#include "Entity.hpp"

enum CollisionCategory
{
    CollisionCategory_DUCK = 0b1 << 0,
    CollisionCategory_STATIC_FOREGROUND = 0b1 << 1,
    CollisionCategory_DYNAMIC_FOREGROUND = 0b1 << 2,
    CollisionCategory_STATIC_BACKGROUND = 0b1 << 3,
    CollisionCategory_DYNAMIC_BACKGROUND = 0b1 << 4,
    CollisionCategory_NO_COLLISION = 0b1 << 5,
    CollisionCategory_ALL_COLLISION = 0b1 << 6
};

#define FOREGROUND_MASK 0b00000110
#define BACKGROUND_MASK 0b00011000

static b2Filter getCollisionFilter(CollisionCategory cc)
{
    b2Filter filter;
    filter.categoryBits = cc;

    switch(cc)
    {
        case CollisionCategory_DUCK:
        filter.maskBits = CollisionCategory_STATIC_FOREGROUND | CollisionCategory_DYNAMIC_FOREGROUND | CollisionCategory_ALL_COLLISION;
            break;
        case CollisionCategory_STATIC_FOREGROUND:
        filter.maskBits = CollisionCategory_DUCK | CollisionCategory_STATIC_FOREGROUND | CollisionCategory_DYNAMIC_FOREGROUND | CollisionCategory_STATIC_BACKGROUND | CollisionCategory_DYNAMIC_BACKGROUND | CollisionCategory_ALL_COLLISION;
            break;
        case CollisionCategory_DYNAMIC_FOREGROUND:
        filter.maskBits = CollisionCategory_DUCK | CollisionCategory_STATIC_FOREGROUND | CollisionCategory_DYNAMIC_FOREGROUND | CollisionCategory_STATIC_BACKGROUND | CollisionCategory_ALL_COLLISION;
            break;
        case CollisionCategory_STATIC_BACKGROUND:
        filter.maskBits = CollisionCategory_STATIC_FOREGROUND | CollisionCategory_DYNAMIC_FOREGROUND | CollisionCategory_STATIC_BACKGROUND | CollisionCategory_DYNAMIC_BACKGROUND | CollisionCategory_ALL_COLLISION;
            break;
        case CollisionCategory_DYNAMIC_BACKGROUND:
        filter.maskBits = CollisionCategory_STATIC_FOREGROUND | CollisionCategory_STATIC_BACKGROUND | CollisionCategory_DYNAMIC_BACKGROUND | CollisionCategory_ALL_COLLISION;
            break;
        case CollisionCategory_NO_COLLISION:
        filter.maskBits = 0x0000;
            break;
        case CollisionCategory_ALL_COLLISION:
        filter.maskBits = 0xFFFF;
    }

    return filter;
}

struct BodyDef
{
    b2BodyDef bodyDef;
    std::vector<std::pair<b2FixtureDef, CollisionCategory>> fixtureDef;

};

class PhysicEntity : public Entity
{
public:

    PhysicEntity();
    PhysicEntity(Scene_Play* play, const sf::Vector2f& position);
    PhysicEntity(Scene_Play* play, const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& rect);
    ~PhysicEntity();
    
    void setPosition(const sf::Vector2f& position);
    void setRotation(float angle);
    void applyImpulse(const sf::Vector2f& impulse);

    virtual void update(const sf::Time deltatime) override;

    b2Body* physicize(b2World& world);

    virtual void onCollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact);
    virtual void onPrecollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact);
    virtual void onDecollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc);
    
    //virtual void onReduceDurability();

    //CollisionCategory getCC() const;
    void getHBs(std::vector<sf::RectangleShape>& hbs) const;

protected:

    b2Body* body; //active body

    void addBody(b2BodyType type, bool fixedrotation = false);
    void addFixture(const b2Shape* shape, CollisionCategory category, float friction, float restitution, float density);
    void addFixture_Sensor(const b2Shape* shape);

    void setBody(unsigned int num, bool sametransform = true);

private:

    bool physicized;

    unsigned int numBodies;
    b2Body** bodies;

    BodyDef** bodyDefs;

    /*
    CollisionCategory cc;
    */
    
    //unsigned int durability;
};

#endif