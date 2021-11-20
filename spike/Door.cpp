
#include "Door.hpp"

#include "Engine/Resources.h"
#include "Utils.hpp"
#include "EntityCreator.hpp"

const sf::Time Door::closeTime = sf::seconds(2.f);

Door::Door(Scene_Play* play, const sf::Vector2f& position) : Object(play, position - sf::Vector2f(0.f, CELLSIZE.y / 2.f))
{
    leftings = rightings = 0;

    setSprite(*Resources::getInstance()->Texture("textures/door.png"), sf::IntRect(ZEROVECTOR_I, sf::Vector2i(CELLSIZE.x, CELLSIZE.y*2)));

    animate(3, sf::seconds(0.05f), false);
    stopAnimation();

    addBody(b2BodyType::b2_staticBody, true);
    addFixture(createRectangle(b2Vec2(CELLSIZE.x/3, CELLSIZE.y*2)), CollisionCategory_STATIC_FOREGROUND, 0.f, 0.f, 1.f); //2
    addFixture_Sensor(createRectangle(b2Vec2(CELLSIZE.x*2, CELLSIZE.y), b2Vec2(CELLSIZE.x, CELLSIZE.y/2))); //0
    addFixture_Sensor(createRectangle(b2Vec2(CELLSIZE.x*2, CELLSIZE.y), b2Vec2(-CELLSIZE.x, CELLSIZE.y/2))); //1

    addSound(*Resources::getInstance()->Sound("sounds/door_open.wav"));
    addSound(*Resources::getInstance()->Sound("sounds/door_close.wav"));

    setCODE(DOOR);
}

Door::~Door() {}

void Door::onCollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact)
{
    printInfo("> DOOR COLLISION --> FIXTURE(" << fixtureid << ") || " << collided->getID());

    switch(fixtureid)
    {
        case 1:
        {
            if(isTarjet(collided, IS_DUCK))
            {
                if(not rightings and not leftings and not timerActive())
                {
                    setSpriteRect(DoorSpriteRect_RIGHT);
                    playAnimation();
                    playSound(0);
                }

                rightings++;
            }
        }
            break;
        case 2:
        {
            if(isTarjet(collided, IS_DUCK))
            {
                if(not leftings and not rightings and not timerActive())
                {
                    setSpriteRect(DoorSpriteRect_LEFT);
                    playAnimation();
                    playSound(0);
                }

                leftings++;
            }
        }
            break;
        default:
            break;
    }
}

void Door::onPrecollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact)
{
    printInfo("> DOOR PRECOLLISION --> FIXTURE(" << fixtureid << ") || " << collided->getID());

    if((timerActive() or rightings or leftings) and not isTarjet(collided, IS_DUCK)) contact->SetEnabled(false);
}

void Door::onDecollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc)
{
    printInfo("> DOOR DECOLLISION --> FIXTURE(" << fixtureid << ") || " << collided->getID());

    switch(fixtureid)
    {
        case 1:
        {
            if(isTarjet(collided, IS_DUCK))
            {
                rightings--;
                if(rightings == 0) startTimer(closeTime);
            }
        }
            break;
        case 2:
        {
            if(isTarjet(collided, IS_DUCK))
            {
                leftings--;
                if(leftings == 0) startTimer(closeTime);
            }
        }
            break;
        default:
            break;
    }
}

void Door::action() {}

void Door::onTimerTrigger()
{
    if(rightings == 0 and leftings == 0)
    {
        setSpriteRect(DoorSpriteRect_CLOSED);
        stopAnimation();
        playSound(1);
    }
}