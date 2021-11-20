
#include "PhysicEntity.hpp"

#include "Utils.hpp"
#include "Utils_Box2D.hpp"
#include "EntityCreator.hpp"

PhysicEntity::PhysicEntity() : Entity()
{
   physicized = false;
   numBodies = 0;

   setCODE(PHYSICENTITY);
}

PhysicEntity::PhysicEntity(Scene_Play* play, const sf::Vector2f& position) : Entity(play, position)
{
    physicized = false;
    numBodies = 0;

    setCODE(PHYSICENTITY);
}

PhysicEntity::PhysicEntity(Scene_Play* play, const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& rect) : Entity(play, position, texture, rect)
{
    physicized = false;
    numBodies = 0;

    setCODE(PHYSICENTITY);
}

PhysicEntity::~PhysicEntity()
{
   if(physicized)
   {
       b2World* world = bodies[0]->GetWorld();

       for(unsigned int i = 0; i < numBodies; i++)
       {
           world->DestroyBody(bodies[i]);
       }

       delete[] bodies;
   }
}

b2Body* PhysicEntity::physicize(b2World& world)
{
    assert(numBodies > 0);

    if(physicized)
    {
        printInfo("Already physicized!");
        return body;
    }

    bodies = new b2Body*[numBodies];

    for(unsigned int i = 0; i < numBodies; i++)
    {
        bodyDefs[i]->bodyDef.position = metrize(tob2Vec2(getPosition()));
        bodies[i] = world.CreateBody(&bodyDefs[i]->bodyDef);

        for(unsigned int j = 0; j < bodyDefs[i]->fixtureDef.size(); j++)
        {
            b2Fixture* tmp = bodies[i]->CreateFixture(&bodyDefs[i]->fixtureDef[j].first);
            tmp->GetUserData().pointer = ((bodyDefs[i]->fixtureDef[j].second << 16) | j);
        }

        bodies[i]->GetUserData().pointer = (uintptr_t)this;
        bodies[i]->SetEnabled(false);

        delete bodyDefs[i];
    }

    delete[] bodyDefs;
    physicized = true;

    bodies[0]->SetEnabled(true);
    body = bodies[0];

    return body;
}

void PhysicEntity::setPosition(const sf::Vector2f& position)
{
    assert(physicized);

    Entity::setPosition(position);
    
    body->SetTransform(tob2Vec2(metrize(position)), body->GetAngle());
}

void PhysicEntity::setRotation(float angle)
{
    assert(physicized);
    
    Entity::setRotation(angle);
    
    body->SetTransform(body->GetPosition(), -1*radize(angle)); //!!
}

void PhysicEntity::applyImpulse(const sf::Vector2f& impulse)
{
    assert(physicized);

    body->ApplyLinearImpulse(metrize(tob2Vec2(impulse)), body->GetWorldCenter(), true);
}

void PhysicEntity::update(const sf::Time deltatime)
{
    Entity::update(deltatime);
    
    if(body->IsAwake())
    {
        Entity::setPosition(pixelize(toVector2f(body->GetPosition())));
        if(not body->IsFixedRotation()) Entity::setRotation(anglize(body->GetAngle()));
    }
}

void PhysicEntity::onPrecollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact) {}

void PhysicEntity::onCollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact) {}

void PhysicEntity::onDecollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc) {}

//void PhysicEntity::onReduceDurability() {}

/*
CollisionCategory PhysicEntity::getCC() const
{
    return CollisionCategory_ALL_COLLISION;
}
*/

void PhysicEntity::getHBs(std::vector<sf::RectangleShape>& hbs) const
{
    hbs.clear();

    sf::RectangleShape hb;

    hb.setFillColor(sf::Color::Transparent);
    hb.setOutlineColor(sf::Color::Magenta);
    hb.setOutlineThickness(-2.f);

    if(physicized)
    {
        b2Fixture* f = body->GetFixtureList();
        while(f != nullptr)
        { 
            b2AABB aabb;
            f->GetShape()->ComputeAABB(&aabb, body->GetTransform(), 0);
            sf::Vector2f hs = toVector2f(pixelize(aabb.GetExtents()));
            hb.setSize(hs*2.f);
            hb.setOrigin(hs);
            hb.setPosition(toVector2f(pixelize(aabb.GetCenter())));

            hbs.push_back(hb);
            
            f = f->GetNext();
        }
    }
}

void PhysicEntity::addBody(b2BodyType type, bool fixedrotation)
{
    numBodies++;

    BodyDef** tmp = new BodyDef*[numBodies];

    if(numBodies > 1)
    {
        memcpy(tmp, bodyDefs, sizeof(BodyDef*) * (numBodies - 1));
        delete[] bodyDefs;
    }
    
    bodyDefs = tmp;

    bodyDefs[numBodies - 1] = new BodyDef();
    b2BodyDef& current = bodyDefs[numBodies - 1]->bodyDef;
    current.type = type;
    current.fixedRotation = fixedrotation;
}

void PhysicEntity::addFixture(const b2Shape* shape, CollisionCategory category, float friction, float restitution, float density)
{
    assert(numBodies > 0);

    BodyDef* bodyDef = bodyDefs[numBodies-1];

    bodyDef->fixtureDef.push_back(std::make_pair(b2FixtureDef(), category));

    b2FixtureDef& current = bodyDef->fixtureDef.back().first;

    current.shape = shape;
    current.friction = friction;
    current.restitution = restitution;
    current.density = density;
    current.filter = getCollisionFilter(category);
    current.isSensor = false;
}

void PhysicEntity::addFixture_Sensor(const b2Shape* shape)
{
    assert(numBodies > 0);

    BodyDef* bodyDef = bodyDefs[numBodies-1];

    bodyDef->fixtureDef.push_back(std::make_pair(b2FixtureDef(), CollisionCategory_ALL_COLLISION));

    b2FixtureDef& current = bodyDef->fixtureDef.back().first;

    current.shape = shape;
    current.friction = 0.f;
    current.restitution = 0.f;
    current.density = 0.f;
    current.filter = getCollisionFilter(CollisionCategory_ALL_COLLISION);
    current.isSensor = true;
}

void PhysicEntity::setBody(unsigned int num, bool sametransform)
{
    assert(num >= 0 and num < numBodies);

    b2Vec2 pos = body->GetPosition();
    b2Vec2 vel = body->GetLinearVelocity();

    body->SetEnabled(false);
    body = bodies[num];
    body->SetEnabled(true);

    if(sametransform)
    {
        body->SetTransform(pos, 0.f);
        body->SetLinearVelocity(vel);
    }
}