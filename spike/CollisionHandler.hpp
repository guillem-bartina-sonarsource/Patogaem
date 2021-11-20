#ifndef COLLISION__HANDLER_HPP
#define COLLISION__HANDLER_HPP

#include <assert.h>

#include "box2d/b2_world_callbacks.h"

class CollisionHandler : public b2ContactListener
{
    public:

    CollisionHandler();
    ~CollisionHandler();
    
    private:

    void BeginContact(b2Contact* contact) override;
    void PreSolve(b2Contact* contact, const b2Manifold *oldManifold) override;
    void EndContact(b2Contact* contact) override;

};

#endif