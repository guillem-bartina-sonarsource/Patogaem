
#include "Object.hpp"

#include "Utils.hpp"
#include "EntityCreator.hpp"

Object::Object()
{
    active = false;

    setCODE(OBJECT);
}

Object::Object(Scene_Play* play, const sf::Vector2f& position) : PhysicEntity(play, position)
{
    active = false;

    setCODE(OBJECT);
}

Object::Object(Scene_Play* play, const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& rect) : PhysicEntity(play, position, texture, rect)
{
    active = false;
    
    setCODE(OBJECT);
}

Object::~Object() {}

void Object::update(const sf::Time deltatime)
{
    PhysicEntity::update(deltatime);
    
    if(active)
    {
        currentTime += deltatime;
        if(currentTime >= triggerTime)
        {
            active = false;
            onTimerTrigger();
        }
    }
}

void Object::action() {}

void Object::startTimer(sf::Time time)
{
    if(not active)
    {
        currentTime = sf::Time::Zero;
        triggerTime = time;
        active = true;
    }
    else
    {
        printInfo(getID() <<  " : TRYING TO ACTIVATE TIMER WHEN ALTERADY ACTIVE");
    }
}

bool Object::timerActive() const
{
    return active;
}

void Object::onTimerTrigger() {}