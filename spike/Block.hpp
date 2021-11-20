#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "PhysicEntity.hpp"

typedef std::pair<unsigned short, unsigned short> Codepair; 

class Block : public PhysicEntity
{
    public:

    Block(Scene_Play* play, const sf::Vector2f& position, unsigned short type);
    ~Block();

    private:

    static const b2EdgeShape edges[4];
    static const std::string types[2];

};

#endif