#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

class EntityRegistryNode;
class Level;

class Entity : public sf::Transformable, public sf::Drawable
{
    public:

    Entity(const sf::Vector2f& position, const sf::Vector2f& size, sf::Sprite* sprite = nullptr);
    ~Entity();

    sf::Vector2f getSize() const;
    virtual void setSize(const sf::Vector2f& size);

    virtual void update(const sf::Time deltatime);

    virtual void levelize(Level* level);

    unsigned int getId() const;
    bool operator==(const Entity& entity) const;
    bool operator<(const Entity& entity) const;

    void debugDraw(sf::RenderTarget& target) const; // TEMPORAL

    protected:

    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* sprite);

    Level* level;
    
    private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    const unsigned int id;

    sf::Vector2f size;

    sf::Sprite* sprite;

    static EntityRegistryNode* node;
    static unsigned int nextId;

};

#endif