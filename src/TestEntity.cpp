
#include "TestEntity.h"

#include "Engine/Resources.h"

#include "Level.h"

//const _EntityRegistryNode* TestEntity::_fixnode = _EntityRegistry::registerClass("TestEntity", Entity::_fixnode);

TestEntity::TestEntity(const sf::Vector2f& position)
: Entity(position, sf::Vector2f(64, 128))
{
    vel = sf::Vector2f(10.f, 5.f);
    sprite = new AnimatedSprite<Anim, Anim::NONE>(*Resources::getInstance()->Texture("textures/duck.png"));
    unsigned int index = sprite->addFrames({
        Frame(sf::IntRect(0, 0, 64, 128)),
        Frame(sf::IntRect(64, 0, 64, 128)),
        Frame(sf::IntRect(128, 0, 64, 128)),
        Frame(sf::IntRect(192, 0, 64, 128)),
        Frame(sf::IntRect(256, 0, 64, 128)),
        Frame(sf::IntRect(320, 0, 64, 128))
    });
    unsigned int index2 = sprite->addFrames({
        Frame(sf::IntRect(0, 128, 64, 128)),
        Frame(sf::IntRect(64, 128, 64, 128)),
        Frame(sf::IntRect(128, 128, 64, 128)),
        Frame(sf::IntRect(192, 128, 64, 128)),
        Frame(sf::IntRect(256, 128, 64, 128)),
        Frame(sf::IntRect(320, 128, 64, 128))
    });
    sprite->addAnimation(Anim::BASE, Animation({
        KeyFrame(index, sf::seconds(0.1f)),
        KeyFrame(index+1, sf::seconds(0.1f)),
        KeyFrame(index+2, sf::seconds(0.1f)),
        KeyFrame(index+3, sf::seconds(0.1f)),
        KeyFrame(index+4, sf::seconds(0.1f)),
        KeyFrame(index+5, sf::seconds(0.1f))
        }, false));
    sprite->addAnimation(Anim::BASE2, Animation({
        KeyFrame(index2, sf::seconds(0.1f)),
        KeyFrame(index2+1, sf::seconds(0.1f)),
        KeyFrame(index2+2, sf::seconds(0.1f)),
        KeyFrame(index2+3, sf::seconds(0.1f)),
        KeyFrame(index2+4, sf::seconds(0.1f)),
        KeyFrame(index2+5, sf::seconds(0.1f))
        }, false));
    sprite->setAnimation(Anim::BASE);
    sprite->setPlaying(true);
    sprite->setScale(0.5f, 0.5f);

    setDrawable(sprite);
}

TestEntity::~TestEntity() {}

void TestEntity::update(const sf::Time deltatime)
{
    sf::Vector2f pos = getPosition();
    if(pos.x < 0 or pos.x > 800)
    {
        vel.x *= -1.f;
    }
    if(pos.y < 0 or pos.y > 670)
    {
        vel.y *= -1.f;
        Entity* entity = new TestEntity(sf::Vector2f(200, 200));
        level->addEntity(entity);
    }
    move(vel * deltatime.asSeconds() * 10.f);
    sprite->update(deltatime);
    if(sprite->hasAnimationEnded())
    {
        if(sprite->getAnimation() == Anim::BASE) sprite->setAnimation(Anim::BASE2);
        else sprite->setAnimation(Anim::BASE);
    }
}
