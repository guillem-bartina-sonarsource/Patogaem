#ifndef ENTITYREGISTRY_HPP
#define ENTITYREGISTRY_HPP

#include <string>
#include <utility>
#include <unordered_map>

#include "Engine/INonCopyable.h"

#include "Entity.h"

class EntityRegistryNode
{
    public:

    EntityRegistryNode(const std::string& name, bool instantiable, EntityRegistryNode* superclass);

    ~EntityRegistryNode();

    void addSubclass(EntityRegistryNode* subclass);

    private:

    const unsigned int code;
    std::string name;
    bool instantiable;

    EntityRegistryNode* superclass;
    std::vector<EntityRegistryNode*> subclasses;

    static unsigned int nextCode;

};

class EntityRegistry : private INonCopyable
{
    public:

    static EntityRegistryNode* registerClass(const std::string& name, bool instantiable, EntityRegistryNode* superclass);
    
    private:

    EntityRegistry();
    ~EntityRegistry();

    static EntityRegistryNode* root;

};

#endif