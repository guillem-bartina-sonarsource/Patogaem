
#include "Level.h"

Level::Level() : world(b2Vec2(0.f, 10.f))
{
    layers.push_back(Layer());
}

Level::~Level()
{
    entities.clear();
}

void Level::addEntity(Entity* entity)
{
    entity->levelize(this, 0);
}

void Level::delEntity(Entity* entity)
{
    entity->unlevelize();
}

void Level::update(const sf::Time& deltatime)
{
    for(auto& entity : entities)
    {
        entity->update(deltatime);
    }
}

void Level::draw(Renderer renderer) const
{
    for(auto& entity : entities)
    {
        renderer(*entity);
    }
}
