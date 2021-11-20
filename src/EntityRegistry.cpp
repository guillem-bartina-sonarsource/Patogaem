
#include "EntityRegistry.hpp"

EntityRegistryNode::EntityRegistryNode(unsigned int code, const std::string& name, bool instantiable, EntityRegistryNode* superclass)
{
    this->code = code;
    this->name = name;
    this->instantiable = instantiable;
    this->superclass = superclass;
}

EntityRegistryNode::~EntityRegistryNode() {}

void EntityRegistryNode::addSubclass(EntityRegistryNode* subclass)
{
    subclasses.push_back(subclass);
}


EntityRegistry::EntityRegistry() {}

EntityRegistry::~EntityRegistry() {}

EntityRegistryNode* EntityRegistry::registerClass(const std::string& name, bool instantiable, EntityRegistryNode* superclass)
{
    EntityRegistryNode* node = new EntityRegistryNode(nextCode++, name, instantiable, superclass);

    if(superclass == nullptr)
    {
        root = node;
    }
    else
    {
        superclass->addSubclass(node);
    }
    return node;
}

EntityRegistryNode* EntityRegistry::root = nullptr;

unsigned int EntityRegistry::nextCode = 0;