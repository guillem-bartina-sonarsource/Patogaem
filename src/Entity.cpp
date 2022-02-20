
#include "Entity.h"

#include "Level.h"

unsigned int Entity::nextId = 0;

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& size, sf::Drawable* drawable)
: level(nullptr),
layer(-1),
id(nextId++),
size(size),
drawable(drawable)
{
    setPosition(position);
}

Entity::~Entity()
{
    if(level)
    {
        unlevelize();
    }
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

void Entity::levelize(Level* level, int layer)
{
    this->level = level;
    this->layer = layer;
    level->entities.insert(this);
    if(drawable)
    {
        level->layers[layer].bindDrawable(drawable);
    }
}

void Entity::unlevelize()
{
    if(drawable)
    {
        level->layers[layer].unbindDrawable(drawable);
    }
    level->entities.erase(this);
    layer = 0;
    level = nullptr;
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

sf::RectangleShape Entity::debug() const
{  
    sf::RectangleShape frame(size);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(-1.f);
    frame.setOutlineColor(sf::Color::Magenta);
    frame.setPosition(getPosition());
    frame.setScale(getScale());
    frame.setRotation(getRotation());
    return frame;
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
