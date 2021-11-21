#ifndef SCENEMENU_HPP
#define SCENEMENU_HPP

#include "SFML/Graphics/Text.hpp"
#include "Engine/IScene.h"

#define NUM_OPTIONS 3

class SceneMenu : public IScene
{
public:

    SceneMenu(int x);
    ~SceneMenu();

    void init(Window::View* window) override;

    void handleEvents(const sf::Event& event) override;

    void update(const sf::Time& deltatime) override;

    void draw(Renderer renderer) const override;

private:

    sf::Text title;
    sf::Text options[NUM_OPTIONS];

    static const std::string texts[NUM_OPTIONS];

    int currentOption;

    bool updateRequest;

    int x;

};

#endif