#ifndef SCENETEST_HPP
#define SCENETEST_HPP

#include "SFML/Graphics/Text.hpp"
#include "Engine/IScene.h"
#include "Engine/AnimatedSprite.hpp"

#include <set>

#include "Entity.h"
#include "Level.h"
#include "_UI/UIBox.h"

struct TestItem
{
    int bullshit;
};

class SceneTest : public IScene
{
    public:

    SceneTest();
    ~SceneTest();

    void init(Window::View* window) override;

    void handleEvents(const sf::Event& event) override;

    void update(const sf::Time& deltatime) override;

    void draw(Renderer renderer) const override;

    private:

    std::string textVar;
    bool boolVar;
    int intVar;

    Level level;

    UIBox* box;

    sf::Texture texture;

    std::set<unsigned int> selected;

};

#endif