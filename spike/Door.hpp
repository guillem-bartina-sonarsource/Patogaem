#ifndef DOOR_HPP
#define DOOR_HPP

#include "Object.hpp"

#include "SFML/Audio/Sound.hpp"

enum DoorSpriteRect
{
    DoorSpriteRect_CLOSED = 0,
    DoorSpriteRect_LEFT,
    DoorSpriteRect_RIGHT
};

class Door : public Object
{
    public:

    Door(Scene_Play* play, const sf::Vector2f& position);
    ~Door();

    void onCollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact) override;
    void onPrecollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact) override;
    void onDecollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc) override;

    virtual void action() override;

    private:
    
    virtual void onTimerTrigger() override;

    static const sf::Time closeTime;

    int leftings, rightings;
    
};

#endif