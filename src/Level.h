#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <unordered_set>

#include "box2d/b2_world.h"

#include "Engine/Common.h"

#include "patogaem/robin_set.h"

#include "Entity.h"
#include "Layer.h"

class Level
{
    public:

    Level();
    ~Level();

    void update(const sf::Time& deltatime);

    void draw(Renderer renderer) const;

    void addEntity(Entity* entity);
    void delEntity(Entity* entity);

    //View for addToLevel functions
    tsl::robin_set<Entity*> entities;
    std::vector<Layer> layers;

    b2World world;

    private:

    //background.
    //class? image, tile (grid, sparse?) effects?

    //List of entities --> For update
    //List of layers of entitites/drawables --> to orgasnize draw
    //List of inputabñe/entotoes -> Observer/Register Pattern

};

#endif