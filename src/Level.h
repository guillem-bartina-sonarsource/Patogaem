#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <map>

#include "Engine/Common.h"

#include "Entity.h"

class Level
{
    public:

    Level();
    ~Level();

    void update(const sf::Time& deltatime);

    void draw(Renderer renderer) const;

    void add(Entity* entity);
    void del(unsigned int id);

    private:

    std::map<unsigned int, Entity*> entities;

    //background.
    //class? image, tile (grid, sparse?) effects?

    //List of entities --> For update
    //List of layers of entitites/drawables --> to orgasnize draw
    //List of inputabñe/entotoes

};

//Level view?

#endif