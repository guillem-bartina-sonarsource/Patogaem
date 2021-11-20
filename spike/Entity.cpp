
#include "Entity.hpp"

#include <iostream>

#include "Utils.hpp"
#include "EntityCreator.hpp"

Entity::Entity()
{
    ID = 0;
    haveSprite = false;
    haveAnimation = false;
    setPosition(ZEROVECTOR_F);
    
    setCODE(ENTITY);
}

Entity::Entity(Scene_Play* play, const sf::Vector2f& position) : play(play)
{
    ID = play->getNextID();
    haveSprite = false;
    haveAnimation = false;
    setPosition(position);
    
    setCODE(ENTITY);
}

Entity::Entity(Scene_Play* play, const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& rect) : play(play)
{
    ID = play->getNextID();
    haveSprite = true;
    haveAnimation = false;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setOrigin(sf::Vector2f(rect.width, rect.height) * 0.5f);
    setPosition(position);
    
    setCODE(ENTITY);
}

Entity::~Entity() {}

void Entity::setPosition(const sf::Vector2f& position)
{
    Transformable::setPosition(position);
    if(haveSprite) sprite.setPosition(position);
}

void Entity::setOrigin(const sf::Vector2f& origin)
{
    Transformable::setOrigin(origin);
    if(haveSprite) sprite.setOrigin(origin);
}

void Entity::setRotation(float angle)
{
    Transformable::setRotation(angle);
    if(haveSprite) sprite.setRotation(angle);
}

void Entity::update(const sf::Time deltatime)
{
    if(haveAnimation and playing)
    {
        currentTime += deltatime;

        if(currentTime >= frameTime)
        {
            currentFrame++;
            currentFrame %= numFrames;

            if(not loop and currentFrame == 0)
            {
                playing = false;
            }
            else
            {
                sf::IntRect rect = sprite.getTextureRect();
                rect.left = rect.width * currentFrame;
                sprite.setTextureRect(rect);

                currentTime -= frameTime;
            }
        }
    }
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(haveSprite) target.draw(sprite, states);
}

bool Entity::operator==(const Entity& e) const
{
    return (ID == e.ID);
}

bool Entity::operator<(const Entity& e) const
{
    return (ID < e.ID);
}

unsigned int Entity::getID() const
{
    return ID;
}

unsigned short Entity::getCODE() const
{
    return CODE;
}

const sf::Sprite* Entity::getSprite() const
{
    if(haveSprite) return &sprite;
    return nullptr;
}

void Entity::animate(unsigned int numFrames, const sf::Time& frameTime, bool loop)
{
    if(haveSprite)
    {
        this->numFrames = numFrames;
        this->frameTime = frameTime;
        this->loop = loop;

        currentFrame = 0;
        currentTime = sf::Time::Zero;

        haveAnimation = true;
        playing = true;
    }
}

void Entity::setAnimationFrame(unsigned int frameNum)
{
    if(haveAnimation and frameNum < numFrames)
    {
        currentFrame = frameNum;

        sf::IntRect rect = sprite.getTextureRect();
        sprite.setTextureRect(sf::IntRect(sf::Vector2i(currentFrame * rect.width, rect.top), sf::Vector2i(rect.width, rect.height)));

        currentTime = sf::Time::Zero;
    }
}

void Entity::playAnimation()
{
    if(haveAnimation) playing = true;
}

void Entity::stopAnimation()
{
    if(haveAnimation)
    {
        setAnimationFrame(0);
        playing = false;
    }
}

void Entity::setCODE(unsigned short code)
{
    CODE = code;
}

void Entity::setSprite(const sf::Texture& texture, const sf::IntRect& rect)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    sprite.setOrigin(sf::Vector2f(rect.width, rect.height) * 0.5f);
    sprite.setPosition(getPosition());
    haveSprite = true;
}

void Entity::setSpriteRect(unsigned int index)
{
    sf::IntRect rect = sprite.getTextureRect();

    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, rect.height*index), sf::Vector2i(rect.width, rect.height)));
}

sf::IntRect Entity::getSpriteRect() const
{
    return sprite.getTextureRect();
}

void Entity::addSound(const sf::SoundBuffer& buffer, float volume)
{
    sf::Sound sound(buffer);
    sound.setVolume(volume);

    sounds.push_back(sound);
}

void Entity::playSound(unsigned int index)
{
    assert(index < sounds.size());

    sounds[index].play();
}
    
