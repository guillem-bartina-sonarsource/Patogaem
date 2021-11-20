#ifndef SCENE__PLAY_HPP
#define SCENE__PLAY_HPP

#define DEBUG_MENU_ENABLE true

#include <queue>

#include "Engine/IScene.h"

#include "box2d/box2d.h"
#include "Utils_Box2D.hpp"

#include "Entity.hpp"
#include "CollisionHandler.hpp"
#include "Level.hpp"

class Entity;

struct EntityComp
{
    bool operator()(const Entity* e1, const Entity* e2) const;
};

typedef std::set<Entity*, EntityComp> EntityHolder;

class Scene_Play : public IScene
{
public:

    Scene_Play(unsigned int levelnum);
    ~Scene_Play();

    void init();

    void handleEvents(const sf::Event& event);

    void update(const sf::Time& deltatime);

    void draw(Renderer renderer) const;

    void pause();

    void resume();

    unsigned int getNextID();

    EntityHolder::iterator createEntity(Entity* entity);
    void destroyEntity(Entity* entity);

    void addEntity(Entity* entity);
    void deleteEntity(Entity* entity);

    const Level& getLevel() const;

private:

    sf::View view;

    //Play vars
    b2World world;
    CollisionHandler collisionHandler;

    sf::RectangleShape background;

    Entity* duck;

    unsigned int ID;
    EntityHolder entities;

    std::queue<Entity*> toDestroy;

    Level level;

    //Functions
    sf::Vector2f cellToPixels(sf::Vector2u cell) const;
    void loadLevel(const Level* level);

    //ImGui vars

    bool duckHBs;
    bool sceneHBs;

    int currentEntity;

    void imgui();
};

#endif