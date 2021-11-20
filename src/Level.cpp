
#include "Level.h"

Level::Level() {}

Level::~Level()
{
    for(auto& entity : entities)
    {
        delete entity.second;
    }
}

void Level::add(Entity* entity)
{
    entities.insert(std::make_pair(entity->getId(), entity));
}

void Level::del(unsigned int id)
{
    entities.erase(id);
}

void Level::update(const sf::Time& deltatime)
{
    for(auto& entity : entities)
    {
        entity.second->update(deltatime);
    }
}

void Level::draw(Renderer renderer) const
{
    for(auto& entity : entities)
    {
        renderer(*entity.second);
    }
}
