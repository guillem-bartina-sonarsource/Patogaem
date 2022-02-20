#ifndef _ENTITYREGISTRY_HPP
#define _ENTITYREGISTRY_HPP

#include <string>
#include <typeinfo>
#include <utility>
#include <functional>
#include <unordered_map>

#include "Engine/INonCopyable.h"

#include "patogaem/fixed_string.hpp"

class Entity;

struct _EntityRegistryNode
{
    _EntityRegistryNode(const std::string& className, _EntityRegistryNode* supernode);
    ~_EntityRegistryNode();

    const std::string className;
    const _EntityRegistryNode* supernode;
    std::vector<const _EntityRegistryNode*> subnodes;

};

class _EntityRegistry
{
    public:

    _EntityRegistry() = delete;

    static _EntityRegistryNode* registerClass(std::size_t classHashCode, const std::string& className, const _EntityRegistryNode* supernode);
    
    static const _EntityRegistryNode* getRoot();

    static void printTree();
    
    static const _EntityRegistryNode* getNode(std::size_t classHashCode);
    static bool isA(const _EntityRegistryNode* currentNode, const _EntityRegistryNode* targetNode);

    private:

    static void printTreeRec(const _EntityRegistryNode* node, int depth);

    static _EntityRegistryNode* root;
    static std::unordered_map<std::size_t, const _EntityRegistryNode*> mapping;

};

template<class EntityClass, class EntitySuperclass, fixstr::fixed_string className>
class _EntityRegistration
{
    public:

    static const _EntityRegistryNode* snode;
};

template<class EntityClass, class EntitySuperclass, fixstr::fixed_string className>
const _EntityRegistryNode* _EntityRegistration<EntityClass, EntitySuperclass, className>::snode = _EntityRegistry::registerClass(typeid(EntityClass).hash_code(), std::string(className), EntitySuperclass::snode);

class _RootEntityRegistration
{
    public:

    static const _EntityRegistryNode* snode;
};


#endif