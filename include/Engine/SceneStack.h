#ifndef SCENESTACK_H
#define SCENESTACK_H

#include <memory>
#include <stack>

#include "INonCopyable.h"
#include "IScene.h"

#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/Drawable.hpp"

class SceneStack : public IScene
{
    public:

    SceneStack(IScene* scene);
    ~SceneStack();

    void init(Window::View* window) override;
    void handleEvents(const sf::Event& event) override;
    void update(const sf::Time& deltatime) override;
    void draw(Renderer render) const override;

    private:

    std::stack<IScene*> scenes;

    Window::View* window;

};

#endif