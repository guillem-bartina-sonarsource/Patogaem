#ifndef _ENTITYREGISTRY_HPP
#define _ENTITYREGISTRY_HPP

#include <string>
#include <utility>
#include <functional>
#include <unordered_map>

#include "Engine/INonCopyable.h"
#include "patogaem/fixed_string.hpp"

class Entity;

class _EntityRegistryNode
{
    public:

    _EntityRegistryNode(const std::string& name, const _EntityRegistryNode* supernode);
    ~_EntityRegistryNode();

    void addSubnode(const _EntityRegistryNode* subnode) const;

    const std::string& getName() const;
    const std::vector<const _EntityRegistryNode*>& getSubnodes() const;

    private:

    const std::string name;

    const _EntityRegistryNode* supernode;
    mutable std::vector<const _EntityRegistryNode*> subnodes;

};

class _EntityRegistry : private INonCopyable
{
    public:

    _EntityRegistry() = delete;

    static _EntityRegistryNode* registerClass(const std::string& name, const _EntityRegistryNode* supernode);
    static const _EntityRegistryNode* getRoot();

    static void printTree();

    private:

    static void printTreeRec(const _EntityRegistryNode* node, int depth);

    static _EntityRegistryNode* root;

};

#endif