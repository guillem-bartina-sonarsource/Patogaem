#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <typeinfo>

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

#include "_EntityRegistry.hpp"

class Level;

class Entity : public sf::Transformable, public sf::Drawable, public _EntityRegistration<Entity, _RootEntityRegistration, "Entity">
{
    public:

    Entity(const sf::Vector2f& position, const sf::Vector2f& size, sf::Drawable* drawable = nullptr);
    virtual ~Entity();

    virtual sf::Vector2f getSize() const;
    virtual void setSize(const sf::Vector2f& size);

    virtual void update(const sf::Time deltatime);

    virtual void levelize(Level* level, int layer);
    virtual void unlevelize();

    unsigned int getId() const;
    bool operator==(const Entity& entity) const;
    bool operator<(const Entity& entity) const;

    sf::RectangleShape debug() const;
    
    //serialize, deserialize...

    protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Drawable* getDrawable() const;
    void setDrawable(sf::Drawable* drawable);

    Level* level;
    int layer;

    public:

    template<class TargetClass>
    static bool isA(const Entity& entity);
    
    private:

    const unsigned int id;

    sf::Vector2f size;

    sf::Drawable* drawable;

    static unsigned int nextId;
};

template<class TargetClass>
bool Entity::isA(const Entity& entity)
{
    return _EntityRegistry::isA(_EntityRegistry::getNode(typeid(entity).hash_code()), TargetClass::snode);
}

#endif