#ifndef PHYSICENTITY_HPP
#define PHYSICENTITY_HPP

#include <vector>

#include "box2d/b2_fixture.h"
#include "box2d/b2_body.h"

#include "Entity.h"

class PhysicEntity : public Entity
{
    public:

    PhysicEntity(const sf::Vector2f& position, const sf::Vector2f& size, sf::Drawable* drawable = nullptr);
    ~PhysicEntity();

    virtual void update(const sf::Time deltatime) override;

    virtual void levelize(Level* level) override;

    protected:

    b2Body* body;
    
    private:

    bool physicized;

    std::vector<b2FixtureDef> fixtureDefs;

};

#endif