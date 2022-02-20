
#include "_EntityRegistry.hpp"

#include <iostream>
#include <typeinfo>

_EntityRegistryNode::_EntityRegistryNode(const std::string& className, _EntityRegistryNode* supernode)
: className(className),
supernode(supernode)
{
    if(supernode)
    {
        supernode->subnodes.push_back(this);
    }
}

_EntityRegistryNode::~_EntityRegistryNode()
{
    for(const _EntityRegistryNode*& subnode : subnodes)
    {
        delete subnode;
    }
}

_EntityRegistryNode* _EntityRegistry::root = nullptr;
std::unordered_map<std::size_t, const _EntityRegistryNode*> _EntityRegistry::mapping;


_EntityRegistryNode* _EntityRegistry::registerClass(std::size_t classHashCode, const std::string& className, const _EntityRegistryNode* supernode)
{
    _EntityRegistryNode* nonconst_supernode = const_cast<_EntityRegistryNode*>(supernode);

    _EntityRegistryNode* node = new _EntityRegistryNode(className, nonconst_supernode);

    mapping.insert(std::make_pair(classHashCode, node));

    if(nonconst_supernode == nullptr)
    {
        root = node;
    }

    return node;
}

const _EntityRegistryNode* _EntityRegistry::getRoot()
{
    return root;
}

void _EntityRegistry::printTree()
{
    if(root)
    {
        printTreeRec(root, 0);
    }
}

void _EntityRegistry::printTreeRec(const _EntityRegistryNode* node, int depth)
{
    std::string out;
    for(int i = 0; i < depth; i++)
    {
        out += " | ";
    }

    out += "- " + node->className;

    std::cout << out << std::endl;

    for(const _EntityRegistryNode* const& subnode : node->subnodes)
    {
        printTreeRec(subnode, depth+1);
    }
}

const _EntityRegistryNode* _EntityRegistry::getNode(std::size_t classHashCode)
{
    return mapping.at(classHashCode);
}

bool _EntityRegistry::isA(const _EntityRegistryNode* object, const _EntityRegistryNode* target)
{
    _EntityRegistryNode const* iter = object;
    while(iter != target and (iter = iter->supernode));
    return iter == target;
}


const _EntityRegistryNode* _RootEntityRegistration::snode = nullptr;
