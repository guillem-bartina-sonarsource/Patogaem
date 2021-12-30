#ifndef IMGUISCENEDECORATOR_H
#define IMGUISCENEDECORATOR_H

#include "IScene.h"

#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class ImguiSceneDecorator : public IScene
{
    public:

    ImguiSceneDecorator(IScene* scene);
    ~ImguiSceneDecorator();

    void init(Window::View* window) override;
    void handleEvents(const sf::Event& event) override;
    void update(const sf::Time& deltatime) override;
    void draw(Renderer render) const override;
    void pause() override;
    void resume() override;

    private:

    IScene* scene;
    Window::View* window;

    mutable sf::RenderTexture renderTexture;
    sf::RectangleShape rectangle;

    sf::Vector2i mousePosition;

};

#endif