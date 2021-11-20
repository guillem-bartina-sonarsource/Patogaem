
#include "Entity.h"

#include "EntityRegistry.hpp"
#include "Level.h"

EntityRegistryNode* Entity::node = EntityRegistry::registerClass("Entity", false, nullptr);

unsigned int Entity::nextId = 0;

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& size, sf::Sprite* sprite)
{
    id = nextId++;
    setPosition(position);
    this->size = size;
    this->sprite = sprite;
    level = nullptr;
}

Entity::~Entity() {}

void Entity::update(const sf::Time deltatime) {}

void Entity::levelize(Level* level)
{
    this->level = level;
    level->add(this);
}

unsigned int Entity::getId() const
{
    return id;
}

bool Entity::operator==(const Entity& entity) const
{
    return (id == entity.id);
}

bool Entity::operator<(const Entity& entity) const
{
    return (id < entity.id);
}

void Entity::debugDraw(sf::RenderTarget& target) const
{
    sf::RenderStates states = sf::RenderStates::Default;
    states.transform *= getTransform();
    
    sf::RectangleShape frame(size);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(-1.f);
    frame.setOutlineColor(sf::Color::Magenta);
    target.draw(frame, states);
}

sf::Sprite* Entity::getSprite()
{
    return sprite;
}

void Entity::setSprite(sf::Sprite* sprite)
{
    if(this->sprite)
    {
        delete this->sprite;
    }
    this->sprite = sprite;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(sprite)
    {
        states.transform *= getTransform();
        target.draw(*sprite, states);
    }
}
