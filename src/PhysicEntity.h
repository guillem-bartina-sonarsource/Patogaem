#ifndef PHYSICENTITY_HPP
#define PHYSICENTITY_HPP

#include <vector>

#include "box2d/b2_fixture.h"
#include "box2d/b2_body.h"

#include "Entity.h"

class PhysicEntity : public Entity, public _EntityRegistration<PhysicEntity, Entity, "PhysicEntity">
{
    public:

    using _EntityRegistration<PhysicEntity, Entity, "PhysicEntity">::snode;

    PhysicEntity(const sf::Vector2f& position, const sf::Vector2f& size, sf::Drawable* drawable = nullptr);
    ~PhysicEntity();

    virtual void update(const sf::Time deltatime) override;

    virtual void levelize(Level* level, int layer) override;
    virtual void unlevelize() override;

    protected:

    b2Body* body;
    
    private:

    bool physicized;

    std::vector<b2FixtureDef> fixtureDefs;

};

#endif