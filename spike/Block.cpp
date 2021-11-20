
#include "Block.hpp"

#include "Engine/Resources.h"
#include "Utils.hpp"
#include "EntityCreator.hpp"

const b2EdgeShape Block::edges[4] = {   
                                        createEdge(b2Vec2(-CELLSIZE.x/2.f, -CELLSIZE.y/2.f), b2Vec2(CELLSIZE.x/2.f, -CELLSIZE.y/2.f)),
                                        createEdge(b2Vec2(CELLSIZE.x/2.f, (-CELLSIZE.y/2.f)), b2Vec2(CELLSIZE.x/2.f, (CELLSIZE.y/2.f))),
                                        createEdge(b2Vec2(CELLSIZE.x/2.f, CELLSIZE.y/2.f), b2Vec2(-CELLSIZE.x/2.f, CELLSIZE.y/2.f)),
                                        createEdge(b2Vec2(-CELLSIZE.x/2.f, (CELLSIZE.y/2.f)), b2Vec2(-CELLSIZE.x/2.f, (-CELLSIZE.y/2.f))) 
                                    };

const std::string Block::types[2] = { "default", "bluecastle" };

Block::Block(Scene_Play* play, const sf::Vector2f& position, unsigned short type) : PhysicEntity(play, position)
{
    int i = position.x / CELLSIZE.x;
    int j = position.y / CELLSIZE.y;

    char sides = 0x0F; //0000 1111

    if(i-1 >= 0 and play->getLevel().containsTarjet(Coord(i-1, j), IS_BLOCK)) sides = sides & 0x0E; //0000 111X
    if(i+1 < NUMCELLS.x and play->getLevel().containsTarjet(Coord(i+1, j), IS_BLOCK)) sides = sides & 0x0B; //0000 1X11
    if(j-1 >= 0 and play->getLevel().containsTarjet(Coord(i, j-1), IS_BLOCK)) sides = sides & 0x07; //0000 X111
    if(j+1 < NUMCELLS.y and play->getLevel().containsTarjet(Coord(i, j+1), IS_BLOCK)) sides = sides & 0x0D; //0000 11X1

    setSprite(*Resources::getInstance()->Texture("textures/" + types[type - BLOCK] + ".png"), sf::IntRect(CELLSIZE.x + ((sides & 0x08) >> 3) * CELLSIZE.x * 3, 0, CELLSIZE.x, CELLSIZE.y)); // change?
    
    addBody(b2BodyType::b2_staticBody);

    for(int i = 0; i < 4; ++i)
    {
        if(sides & (0x08 >> i)) addFixture(&edges[i], CollisionCategory_STATIC_FOREGROUND, 0.5f, 0.f, 1.f);
    }

    setCODE(type);
}

Block::~Block() {}