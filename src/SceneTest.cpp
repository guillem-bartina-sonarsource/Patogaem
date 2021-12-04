
#include "SceneTest.h"

#include "SFML/Graphics/RectangleShape.hpp"

#include "Engine/Resources.h"

#include "TestEntity.h"
#include "UIBox.h"
#include "UIBorder.h"
#include "UIRect.h"
#include "UILabel.h"

SceneTest::SceneTest() : IScene() {}

SceneTest::~SceneTest() {}

void SceneTest::init(Window::View* window)
{
    Entity* entity = new TestEntity(sf::Vector2f(100, 100));
    entity->levelize(&level);

    //UIRect* rect = new UIRect(UIRectStyle::defaultStyle(), EUIAlign::TOPLEFT, EUIFit::ADJUST, sf::Vector2f(), sf::Vector2f(100, 100));
    //UIBox* box = new UIBox(sf::Vector2f(100, 100), sf::Vector2f(400, 400), rect);
    UILabel* label = new UILabel("hello this a text", UILabelStyle::defaultStyle(*Resources::getInstance()->Font("fonts/font.ttf")), EUIAlign::TOPLEFT, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f());
    UIBox* box = new UIBox(sf::Vector2f(100, 100), sf::Vector2f(400, 400), new UIBorder(UIBorderStyle{sf::Color::Red, 5.f, 10.f}, label));
    box->levelize(&level);

    this->box = box;
}

void SceneTest::handleEvents(const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Escape:
                {
                    closeScene();
                }
                    break;
                default:
                    break;
            }
        }
            break;        
        default:
            break;
    }

    box->handleEvents(event);
}

void SceneTest::update(const sf::Time& deltatime)
{
    level.update(deltatime);
}

void SceneTest::draw(Renderer renderer) const
{
    level.draw(renderer);
}
