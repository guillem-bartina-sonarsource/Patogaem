
#include "Duck.hpp"

#include <cmath>

#include "Engine/Resources.h"
#include "Utils.hpp"
#include "EntityCreator.hpp"

const float Duck::dynamicsValues[5] = {7.f, 7.f, 4.5f, 0.f, 10.f};
const float Duck::dynamicsCoefs[5] = {0.75f, 0.85f, 0.85f, 0.f, 0.95f};
const sf::Vector2f Duck::holdableOffset[5] = {sf::Vector2f(20, 0), sf::Vector2f(20, 0), sf::Vector2f(20, 0), sf::Vector2f(20, 20), sf::Vector2f(0, 20)};

Duck::Duck(Scene_Play* play, const sf::Vector2f& position) : PhysicEntity(play, position)
{
    //Duck vars
    state = MovementState_JUMPING;
    side = MovementSide_RIGHT;

    holdable = nullptr;

    groundings = headings = 0;

    pL = pR = pU = pD = false;

    changecicle = -1;

    tk = false;
    alive = true;

    //Image
    setSprite(*Resources::getInstance()->Texture("textures/duck.png"), sf::IntRect(0, 0, CELLSIZE.x, CELLSIZE.y*2));

    animate(6, sf::seconds(0.1f));
    stopAnimation();

    //Bodies
    addBody(b2BodyType::b2_dynamicBody, true);

    //-->0
    addFixture(createRectangle(b2Vec2(CELLSIZE.x-2, (CELLSIZE.y*2)-2)), CollisionCategory_DUCK, 0.f, 0.f, 1.f); //0
    addFixture_Sensor(createRectangle(b2Vec2(CELLSIZE.x-12, 20), b2Vec2(0, 53))); //1
    addFixture_Sensor(createRectangle(b2Vec2(CELLSIZE.x-12, 20), b2Vec2(0, -53))); //2
    addFixture_Sensor(createRectangle(b2Vec2(CELLSIZE.x-2, (CELLSIZE.y*2)-2))); //3

    //-->1
    addBody(b2BodyType::b2_dynamicBody, true);

    addFixture(createRectangle(b2Vec2(CELLSIZE.x-2, 88-2), b2Vec2(0, 20)), CollisionCategory_DUCK, 0.f, 0.f, 1.f); //0
    addFixture_Sensor(createRectangle(b2Vec2(CELLSIZE.x-12, 20), b2Vec2(0, 53))); //1
    addFixture_Sensor(createRectangle(b2Vec2(CELLSIZE.x-12, 20), b2Vec2(0, -13))); //2
    addFixture_Sensor(createRectangle(b2Vec2(CELLSIZE.x-2, 88-2), b2Vec2(0, 20))); //3

    //-->2
    addBody(b2BodyType::b2_dynamicBody, true);

    addFixture(createRectangle(b2Vec2((CELLSIZE.x*2)-4, CELLSIZE.y-2), b2Vec2(0, 32)), CollisionCategory_DUCK, 0.f, 0.f, 1.f); //0 //change width??
    addFixture_Sensor(createRectangle(b2Vec2(CELLSIZE.x-12, 20), b2Vec2(0, 53))); //1
    addFixture_Sensor(createRectangle(b2Vec2((CELLSIZE.x*2)-62, 20), b2Vec2(0, 11))); //2
    addFixture_Sensor(createRectangle(b2Vec2((CELLSIZE.x*2)-4, CELLSIZE.y-2), b2Vec2(0, 32))); //3

    //-->3
    addBody(b2BodyType::b2_dynamicBody, true);

    addFixture(createRectangle(b2Vec2(CELLSIZE.x-2, CELLSIZE.y-2), b2Vec2(0, 32)), CollisionCategory_DYNAMIC_BACKGROUND, 0.f, 0.f, 1.f); //0

    //---

    //clean code and calls to body, swithes,...
    //restore ground/head on changebody

    addSound(*Resources::getInstance()->Sound("sounds/quack.wav"));

    setCODE(DUCK);

    change = false;    
}

Duck::~Duck() {}

void Duck::handleEvents(const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    if(state == MovementState_STANDING and not headings) //groundings?
                    {
                        body->ApplyLinearImpulse(b2Vec2(0, -32), body->GetWorldCenter(), true);
                        //changeState(MovementState_JUMPING);
                        change = true;
                        newstate = MovementState_JUMPING;
                    }
                    else if(state == MovementState_JUMPING)
                    {
                        //changeState(MovementState_FLYING);
                        change = true;
                        newstate = MovementState_FLYING;
                    }
                    pU = true;
                }
                    break;
                case sf::Keyboard::Down:
                {
                    switch(state)
                    {
                        case MovementState_STANDING:
                        {
                            if(pL xor pR)
                            {
                                //changeState(MovementState_FLOORING);
                                change = true;
                                newstate = MovementState_FLOORING;
                            }
                            else
                            {
                                //changeState(MovementState_DOWNING);
                                change = true;
                                newstate = MovementState_DOWNING;
                            }
                        }
                            break;
                        default:
                            break;
                    }
                    pD = true;
                }
                    break;
                case sf::Keyboard::Left:
                {
                    switch(state)
                    {
                        case MovementState_FLOORING:
                        {
                            if(side == MovementSide_LEFT) body->ApplyLinearImpulse(b2Vec2(-dynamicsValues[state]/2.f * body->GetMass(), 0.f), body->GetWorldCenter(), true);
                        }
                            break;
                        default:
                        {
                            side = MovementSide_LEFT;
                        }
                            break;
                    }
                    pL = true;
                }
                    break;
                case sf::Keyboard::Right:
                {
                    switch(state)
                    {
                        case MovementState_FLOORING:
                        {
                            if(side == MovementSide_RIGHT) body->ApplyLinearImpulse(b2Vec2(dynamicsValues[state]/2.f * body->GetMass(), 0.f), body->GetWorldCenter(), true);
                        }
                            break;
                        default:
                        {
                            side = MovementSide_RIGHT;
                        }
                            break;
                    }
                    pR = true;
                }
                    break;
                case sf::Keyboard::E:
                {
                    playSound(0);
                    std::cerr << "------------" << std::endl;
                }
                    break;
                case sf::Keyboard::C:
                {
                    if(holdable == nullptr)
                    {
                        if(not holdables.empty())
                        {
                            holdable = (*holdables.begin())->get();
                            holdables.erase(holdable);

                            play->deleteEntity(static_cast<Entity*>(holdable));
                            holdable->setPosition(getPosition());
                        }
                    }
                    else
                    {
                        sf::Vector2f impulse = ZEROVECTOR_F;

                        if(pL xor pR)
                        {
                            impulse.x = (pL ? -25.f : 25.f);

                            if(pU) impulse.y = -20.f;
                        }
                        else if(pU) impulse.y = -15.f;


                        play->addEntity(holdable->unget(impulse));
                        holdable = nullptr;
                    }
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case sf::Event::KeyReleased:
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    if(not groundings and state == MovementState_FLYING)
                    {
                        //changeState(MovementState_JUMPING);
                        change = true;
                        newstate = MovementState_JUMPING;
                    }
                    else if(state == MovementState_JUMPING)
                    {
                        body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, body->GetLinearVelocity().y * 0.6f));
                    }
                    pU = false;
                }
                    break;
                case sf::Keyboard::Down:
                {
                    switch(state)
                    {
                        case MovementState_DOWNING:
                        {
                            //changeState(MovementState_STANDING);
                            change = true;
                            newstate = MovementState_STANDING;
                        }
                            break;
                        case MovementState_FLOORING:
                        {
                            if(not headings)
                            {
                                //changeState(MovementState_STANDING);
                                change = true;
                                newstate = MovementState_STANDING;
                                if(pL and not pR) side = MovementSide_LEFT;
                                else if(pR and not pL) side = MovementSide_RIGHT;
                            }
                        }
                            break;
                        default:
                            break;
                    }
                    pD = false;
                }
                    break;
                case sf::Keyboard::Left:
                {
                    if(state != MovementState_FLOORING)
                    {
                        if(pR) side = MovementSide_RIGHT;
                    }
                    pL = false;
                }
                    break;
                case sf::Keyboard::Right:
                {
                    if(state != MovementState_FLOORING)
                    {
                        if(pL) side = MovementSide_LEFT;
                    }
                    pR = false;
                }
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }

    setSpriteRect((getSpriteRect().top/256)*2+side);
}

void Duck::update(const sf::Time deltatime)
{
    PhysicEntity::update(deltatime);

    if(changecicle >= 0) changecicle++;
    
    if(changecicle == 2)
    {
        ignoring = ignoringNew;
        ignoringNew.clear();

        changecicle = -1;
    }

    while(not toDelete.empty())
    {
        ignoring.erase(toDelete.front());
        toDelete.pop();
    }

    if(tk)
    {
        kill();
        tk = false;
    }

    bool ableToMove = (state != MovementState_FLOORING and state != MovementState_DOWNING);
    if(ableToMove and (pL xor pR))
    {
        b2Vec2 currentVel = body->GetLinearVelocity();
        float idealVel = dynamicsValues[state] * std::pow(-1, (int)side);
        float impulse = body->GetMass() * (idealVel - currentVel.x);
        body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
        if(state == MovementState_STANDING) playAnimation();
        else stopAnimation();
    }
    else
    {
        b2Vec2 currentVel = body->GetLinearVelocity();
        if(std::abs(currentVel.x) > 0.05f)
        {
            float idealVel = currentVel.x * dynamicsCoefs[state]; //diferent coefs?
            float impulse = body->GetMass() * (idealVel - currentVel.x);
            body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
        }
        else body->SetLinearVelocity(b2Vec2(0.f, currentVel.y));
        stopAnimation();
    }

    if(state == MovementState_FLYING and body->GetLinearVelocity().y > 0.f)
    {
        body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, std::min(body->GetLinearVelocity().y, 2.f)));
    }

    if(holdable != nullptr) holdable->setPosition(getPosition() + sf::Vector2f(holdableOffset[state].x * std::pow(-1.f, (int)side), holdableOffset[state].y));

    if(change)
    {
        changeState(newstate);
    
        change = false;
    }
}

void Duck::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Entity::draw(target, states);
    if(holdable != nullptr) target.draw(*holdable, states);
}

void Duck::onCollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact)
{
    printInfo("> DUCK COLLISION --> FIXTURE(" << fixtureid << ") || " << collided->getID());

    switch(fixtureid)
    {
        case 0:
        {
            if(isTarjet(collided, IS_CRATE))
            {
                b2WorldManifold wm;
                contact->GetWorldManifold(&wm);

                if(wm.normal.y != 1)
                {
                    ignoring.insert(collided->getID());
                }
            }
        }
            break;
        case 1:
        {
            if(cc & FOREGROUND_MASK)
            {
                if(ignoring.find(collided->getID()) == ignoring.end())
                {
                    if(groundings == 0)
                    {
                        if(state == MovementState_FLYING or state == MovementState_JUMPING)
                        {
                            change = true;
                            if(pD) newstate = MovementState_DOWNING;
                            else newstate = MovementState_STANDING;
                        }
                    }

                    groundings++;
                }
            }
        }
            break;
        case 2:
        {
            if(cc & FOREGROUND_MASK)
            {
                if(ignoring.find(collided->getID()) == ignoring.end())
                {
                    headings++;
                }
            }
        }
            break;
        case 3:
        {
            if(isTarjet(collided, IS_HOLDABLE))
            {
                holdables.insert(static_cast<Holdable*>(collided));
            }

            if(changecicle == 1)
            {
                if(ignoring.find(collided->getID()) != ignoring.end())
                {
                    ignoringNew.insert(collided->getID());
                }
            }
        }
            break;
        default:
            break;
    }
}

void Duck::onPrecollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc, b2Contact* contact)
{
    printInfo("> DUCK PRECOLLISION --> FIXTURE(" << fixtureid << ") || " << collided->getID());

    if(isTarjet(collided, IS_CRATE))
    {
        if(ignoring.find(collided->getID()) != ignoring.end()) contact->SetEnabled(false);
    }
    else if(isTarjet(collided, IS_DOOR))
    {
        contact->SetEnabled(false);
    }
}

void Duck::onDecollision(unsigned short fixtureid, PhysicEntity* collided, unsigned short cc)
{
    printInfo("> DUCK DECOLLISION --> FIXTURE(" << fixtureid << ") || " << collided->getID());

    switch(fixtureid)
    {
        case 0: //ORDER OF DECOLLISION??
        {
        }
            break;
        case 1:
        {
            if(cc & FOREGROUND_MASK)
            {
                if(ignoring.find(collided->getID()) == ignoring.end())
                {
                    groundings--;
                    if(groundings == 0)
                    {
                        if(state == MovementState_STANDING)
                        {
                            change = true; 
                            newstate = MovementState_JUMPING;
                        }
                    }
                }
            }
        }
            break;
        case 2:
        {
            if(cc & FOREGROUND_MASK)
            {
                if(ignoring.find(collided->getID()) == ignoring.end())
                {
                    headings--;
                    if(headings == 0)
                    {
                        if(state == MovementState_FLOORING and not pD)
                        {
                            change = true;
                            newstate = MovementState_STANDING;
                        }
                    }
                }
            }
        }
            break;
        case 3:
        {
            if(isTarjet(collided, IS_HOLDABLE))
            {
                holdables.erase(static_cast<Holdable*>(collided));
            }

            if(changecicle == -1)
            {
                if(ignoring.find(collided->getID()) != ignoring.end()) toDelete.push(collided->getID());
            }
        }
            break;
        default:
            break;
    }
}

void Duck::kill()
{
    setBody(3);
    setSpriteRect(6+side);

    alive = false;
}

bool Duck::isAlive() const
{
    return alive;
}

MovementState Duck::getState() const
{
    return state;
}

unsigned int Duck::getHeadings() const
{
    return headings;
}

unsigned int Duck::getGroundings() const
{
    return groundings;
}

void Duck::changeState(MovementState newstate)
{
    printInfo(" > Changed state to " << MovementState_String[newstate] << std::endl);
    switch(newstate)
    {
        case MovementState_STANDING:
        case MovementState_JUMPING:
        case MovementState_FLYING:
        {
            if(state == MovementState_DOWNING or state == MovementState_FLOORING)
            {
                changecicle = 0;
                setBody(0);
                setSpriteRect(0+side);
            }
        }
            break;
        case MovementState_DOWNING:
        {
            if(state != MovementState_DOWNING)
            {
                changecicle = 0;
                setBody(1);
                setSpriteRect(2+side);
            }
        }
            break;
        case MovementState_FLOORING:
        {
            if(state != MovementState_FLOORING)
            {
                changecicle = 0;
                setBody(2);
                setSpriteRect(4+side);
                body->ApplyLinearImpulse(b2Vec2(dynamicsValues[state] * std::pow(-1, (int)side) * body->GetMass(), 0), body->GetWorldCenter(), true); //PULSE, change?
            }
        }
            break;
    };

    state = newstate;
}