
#include "_EntityRegistry.h"

#include <iostream>

_EntityRegistryNode::_EntityRegistryNode(const std::string& name, const _EntityRegistryNode* supernode)
: name(name),
supernode(supernode)
{
    if(supernode)
    {
        supernode->addSubnode(this);
    }
}

_EntityRegistryNode::~_EntityRegistryNode() {}

void _EntityRegistryNode::addSubnode(const _EntityRegistryNode* subnode) const
{
    subnodes.push_back(subnode);
}

const std::string& _EntityRegistryNode::getName() const
{
    return name;
}


_EntityRegistryNode* _EntityRegistry::root = nullptr;

_EntityRegistryNode* _EntityRegistry::registerClass(const std::string& name, const _EntityRegistryNode* superclass)
{
    _EntityRegistryNode* node = new _EntityRegistryNode(name, superclass);

    if(superclass == nullptr)
    {
        root = node;
    }

    return node;
}

const _EntityRegistryNode* _EntityRegistry::getRoot()
{
    return root;
}

const std::vector<const _EntityRegistryNode*>& _EntityRegistryNode::getSubnodes() const
{
    return subnodes;
}

void _EntityRegistry::printTree()
{
    printTreeRec(root, 0);
}

void _EntityRegistry::printTreeRec(const _EntityRegistryNode* node, int depth)
{
    std::string out;
    for(int i = 0; i < depth; i++)
    {
        out += " | ";
    }

    out += "- " + node->getName();

    std::cout << out << std::endl;

    for(const _EntityRegistryNode* const& subnode : node->getSubnodes())
    {
        printTreeRec(subnode, depth+1);
    }
}
