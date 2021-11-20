#ifndef ENTITYREGISTRY_HPP
#define ENTITYREGISTRY_HPP

#include <string>
#include <utility>
#include <unordered_map>

#include "Engine/INonCopyable.h"

#include <Entity.h>

class EntityRegistryNode
{
    public:

    EntityRegistryNode(unsigned int code, const std::string& name, bool instantiable, EntityRegistryNode* superclass);

    ~EntityRegistryNode();

    void addSubclass(EntityRegistryNode* subclass);

    private:

    unsigned int code;
    std::string name;
    bool instantiable;

    EntityRegistryNode* superclass;
    std::vector<EntityRegistryNode*> subclasses;

};

class EntityRegistry : private INonCopyable
{
    public:

    static EntityRegistryNode* registerClass(const std::string& name, bool instantiable, EntityRegistryNode* superclass);
    
    private:

    EntityRegistry();
    ~EntityRegistry();

    static EntityRegistryNode* root;

    static unsigned int nextCode;

};

#endif