
#include "Entity.h"

#include "EntityRegistry.h"
#include "Level.h"

EntityRegistryNode* Entity::node = EntityRegistry::registerClass("Entity", false, nullptr);

unsigned int Entity::nextId = 0;

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& size, sf::Drawable* drawable)
: id(nextId++)
{
    setPosition(position);
    this->size = size;
    this->drawable = drawable;
    level = nullptr;
}

Entity::~Entity()
{
    if(drawable)
    {
        delete drawable;
    }
}

sf::Vector2f Entity::getSize() const
{
    return size;
}

void Entity::setSize(const sf::Vector2f& size)
{
    this->size = size;
}

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

sf::Drawable* Entity::getDrawable() const
{
    return drawable;
}

void Entity::setDrawable(sf::Drawable* drawable)
{
    if(this->drawable)
    {
        delete this->drawable;
    }
    this->drawable = drawable;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(drawable)
    {
        states.transform *= getTransform();
        target.draw(*drawable, states);
    }
}
