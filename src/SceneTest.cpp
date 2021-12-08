
#include "SceneTest.h"

#include "SFML/Graphics/RectangleShape.hpp"

#include "Engine/Resources.h"

#include "TestEntity.h"
#include "UIBox.h"
#include "UIBorder.h"
#include "UIRect.h"
#include "UILabel.h"
#include "UICanvas.h"
#include "UIButton.h"

SceneTest::SceneTest() : IScene() {}

SceneTest::~SceneTest() {}

void SceneTest::init(Window::View* window)
{
    Entity* entity = new TestEntity(sf::Vector2f(100, 100));
    entity->levelize(&level);

    UIRect* rect = new UIRect(UIRectStyle{sf::Color::Blue, -5.f, sf::Color::Yellow}, EUIAlign::TOPLEFT, EUIFit::EUIFit_NONE, sf::Vector2f(0.f, 0.f), sf::Vector2f(600, 600));
    //UIBox* box = new UIBox(sf::Vector2f(100, 100), sf::Vector2f(400, 400), rect);
    //UILabel* label = new UILabel("hello this a text", UILabelStyle::defaultStyle(*Resources::getInstance()->Font("fonts/font.ttf")), EUIAlign::TOPLEFT, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f());
    //UICanvas* canvas0 = new UICanvas(sf::Vector2f(600, 600), UICanvasStyle{EUICanvasVerticalSliderPosition::RIGHT, EUICanvasHorizontalSliderPosition::BOTTOM, 10.f, 10}, rect);
    //UICanvas* canvas = new UICanvas(sf::Vector2f(500, 500), UICanvasStyle{EUICanvasVerticalSliderPosition::RIGHT, EUICanvasHorizontalSliderPosition::BOTTOM, 10.f, 10}, canvas0);
    UIButton* button = new UIButton([](){}, EUIAlign::TOPLEFT, EUIFit::EUIFit_NONE, sf::Vector2f(0.f, 0.f), sf::Vector2f(100, 100));
    UIBox* box = new UIBox(sf::Vector2f(100, 100), sf::Vector2f(400, 400), new UIBorder(UIBorderStyle{sf::Color::Red, 5.f}, button));
    //UIBox* box = new UIBox(sf::Vector2f(100, 100), sf::Vector2f(400, 400), canvas);
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
