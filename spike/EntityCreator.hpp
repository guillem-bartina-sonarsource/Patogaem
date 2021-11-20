#ifndef ENTITYCREATOR_HPP
#define ENTITYCREATOR_HPP

#include <iostream>

//All includes...
#include "Entity.hpp"
#include "GenericEntity.hpp"

#include "PhysicEntity.hpp"
#include "GenericPhysicEntity.hpp"
#include "Block.hpp"

#include "Object.hpp"
#include "Door.hpp"

#include "Holdable.hpp"
#include "Crate.hpp"

enum EntityCode
{
    ENTITY = 0x0000,
    GENERICENTITY = 0x0001,

    PHYSICENTITY = 0x8000,
    GENERICPHYSICENTITY = 0x8001,
    DUCK = 0xC001,
    BLOCK = 0xC008,
    BLOCK_BLUECASTLE = 0xC009,

    OBJECT = 0xE000,
    DOOR = 0xE081,

    HOLDABLE = 0xF000,
    CRATE = 0xF001
};

static Entity* getEntitybyCode(EntityCode ic, Scene_Play* play, const sf::Vector2f& position)
{
    switch(ic)
    {
        case ENTITY:
            return new Entity();
            break;
        case GENERICENTITY:
            return new GenericEntity(play, position, "test");
            break;
        case PHYSICENTITY:
            return new PhysicEntity();
            break;
        case GENERICPHYSICENTITY:
            return new GenericPhysicEntity(play, position, "test");
            break;
        //DUCK IN SCENE_PLAY EXPLICIT
        case BLOCK:
            return new Block(play, position, BLOCK);
            break;
        case BLOCK_BLUECASTLE:
            return new Block(play, position, BLOCK_BLUECASTLE);
            break;
        case OBJECT:
            return new Object();
            break;
        case DOOR:
            return new Door(play, position);
            break;
        case HOLDABLE:
            return new Holdable();
            break;
        case CRATE:
            return new Crate(play, position);
            break;
        default:
            assert(false);
            return nullptr;
            break;
    }
};

typedef std::pair<unsigned short, unsigned short> Codepair; //code + mask

static bool isTarjet(const Entity* entity, const Codepair& codepair)
{
    return (((entity->getCODE() & codepair.second) ^ codepair.first) == 0x0000);
};

static bool isTarjet(unsigned short CODE, const Codepair& codepair)
{
    return (((CODE & codepair.second) ^ codepair.first) == 0x0000);
};

static const Codepair IS_ENTITY = std::make_pair(ENTITY, 0x0000); //XXXX XXXX XXXX XXXX
static const Codepair IS_GENERICENTITY = std::make_pair(GENERICENTITY, 0xFFFF); //0000 0000 0000 0001
//static const Codepair IS_OTHERENTITIES = std::make_pair(0x6000, 0xC000); //01XX XXXX XXXX XXXX

static const Codepair IS_PHYSICENTITY = std::make_pair(PHYSICENTITY, 0x8000); //1XXX XXXX XXXX XXXX
static const Codepair IS_GENERICPHYSICENTITY = std::make_pair(GENERICPHYSICENTITY, 0xFFFF); //1000 0000 0000 0001

static const Codepair IS_DUCK = std::make_pair(DUCK, 0xFFFF); //1000 0000 0000 1001
static const Codepair IS_BLOCK = std::make_pair(BLOCK, 0xFFF8); //1000 0000 0000 1000
static const Codepair IS_BLOCK_BLUECASTLE = std::make_pair(BLOCK_BLUECASTLE, 0xFFFF); //1000 0000 0000 1001
//static const Codepair IS_OTHERPHYSICENTITIES = std::make_pair(0xC000, 0xC000); //11XX XXXX XXXX XXXX

static const Codepair IS_OBJECT = std::make_pair(OBJECT, 0xE000); //111X XXXX XXXX XXXX
static const Codepair IS_DOOR = std::make_pair(DOOR, 0xFFFF); //1110 0000 0000 0001

static const Codepair IS_HOLDABLE = std::make_pair(HOLDABLE, 0xF000); //1111 XXXX XXXX XXXX
static const Codepair IS_CRATE = std::make_pair(CRATE, 0xFFFF); //1111 0000 0000 0001


//---

static const char* Entity_String[10] = {"Entity", "GenericEntity", "PhysicEntity", "GenericPhysicEntity", "Block", "Block_Bluecastle", "Object", "Door", "Holdable", "Crate" };
static const EntityCode Entity_Code[10] = {ENTITY, GENERICENTITY, PHYSICENTITY, GENERICPHYSICENTITY, BLOCK, BLOCK_BLUECASTLE, OBJECT, DOOR, HOLDABLE, CRATE};

/*
CRATE
BIDON
TROWABLES:
    GRENADE
    FLAMEBOMB
GUNS:
    PISTOL
    SHOTGUN
    MP5
    RAY
    REVOLVER
    TRAP

*/

#endif