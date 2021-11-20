#ifndef SCENETEST_HPP
#define SCENETEST_HPP

#include "SFML/Graphics/Text.hpp"
#include "Engine/IScene.h"
#include "Engine/AnimatedSprite.hpp"

#include "Entity.h"
#include "Level.h"

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

    Level level;

};

#endif