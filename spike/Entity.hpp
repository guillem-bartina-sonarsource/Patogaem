#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

#include "Scene_Play.hpp"

class Scene_Play;

class Entity : public sf::Transformable, public sf::Drawable
{
public:

    Entity();
    Entity(Scene_Play* play, const sf::Vector2f& position);
    Entity(Scene_Play* play, const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& rect);
    ~Entity();

    void setPosition(const sf::Vector2f& position);
    void setOrigin(const sf::Vector2f& origin);
    void setRotation(float angle);

    virtual void update(const sf::Time deltatime);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool operator==(const Entity& e) const;
    bool operator<(const Entity& e) const;

    unsigned int getID() const;
    unsigned short getCODE() const;

    const sf::Sprite* getSprite() const;
    
protected:

    void animate(unsigned int numFrames, const sf::Time& frameTime, bool loop = true);
    void setAnimationFrame(unsigned int frameNum);
    void playAnimation();
    void stopAnimation();

    void setCODE(unsigned short code);
    void setSprite(const sf::Texture& texture, const sf::IntRect& rect);
    void setSpriteRect(unsigned int index);
    sf::IntRect getSpriteRect() const;

    void addSound(const sf::SoundBuffer& buffer, float volume = 80.f);
    void playSound(unsigned int index);

    Scene_Play* play;

private:

    unsigned int ID;
    unsigned short CODE; //default: 0

    bool haveSprite;
    sf::Sprite sprite;
    
    bool haveAnimation;
    bool playing;
    bool loop;
    unsigned int numFrames;
    sf::Time frameTime;

    unsigned int currentFrame;
    sf::Time currentTime;

    std::vector<sf::Sound> sounds;

};

#endif