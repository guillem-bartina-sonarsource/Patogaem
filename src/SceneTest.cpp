
#include "SceneTest.h"

#include "SFML/Graphics/RectangleShape.hpp"

#include "Engine/Resources.h"

#include "TestEntity.h"
#include "PhysicEntity.h"

#include "_UI/UI.h"

SceneTest::SceneTest() : IScene() {}

SceneTest::~SceneTest()
{
    for(auto i : selected)
    {
        std::cout << i << std::endl;
    }
}

void SceneTest::init(Window::View* window)
{
    Entity* entity = new TestEntity(sf::Vector2f(100, 100));
    level.addEntity(entity);


    /*
    const sf::Font* font = Resources::getInstance()->Font("fonts/font.ttf");

    for(unsigned char c = 0; c < 200; c++)
    {
        sf::Glyph g = font->getGlyph(c, 24, false);
    }

    texture = font->getTexture(24);
    */

    //UIRect* rect = new UIRect(UIRectStyle{sf::Color::Blue, -5.f, sf::Color::Yellow, &texture, std::optional<sf::IntRect>(sf::IntRect(sf::Vector2i(), sf::Vector2i(texture.getSize())))}, EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(0.f, 0.f), sf::Vector2f(-1.f, -1.f));
    //UIBox* box = new UIBox(sf::Vector2f(100, 100), sf::Vector2f(400, 400), rect);
    //UILabel* label = new UILabel("hello this a text", UILabelStyle::defaultStyle(*Resources::getInstance()->Font("fonts/font.ttf")), EUIAlign::TOPLEFT, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f());
    //UICanvas* canvas0 = new UICanvas(sf::Vector2f(600, 600), UICanvasStyle{EUICanvasVerticalSliderPosition::RIGHT, EUICanvasHorizontalSliderPosition::BOTTOM, 10.f, 10}, rect);
    //UIButton* button = new UIButton([](){}, EUIAlign::TOPLEFT, EUIFit::EUIFit_NONE, sf::Vector2f(0.f, 0.f), sf::Vector2f(100, 100));
    
    //UIItemList<TestItem>* itemList = new  UIClickableItemList<TestItem>([](TestItem ti){ std::cout << ti.bullshit << " "; }, EUIItemListOrientation_VERTICAL, 200.f, [](TestItem item){ return new UIButton([](){}, UIButtonStyle::defaultStyle(), EUIAlign::CENTERCENTER, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(50, 50));}, std::vector<TestItem>{TestItem{0}, TestItem{1}, TestItem{2}, TestItem{3}});
    
    UISelectableItemList<TestItem>* itemList = new  UISelectableItemList<TestItem>(&selected, true, EUIItemListOrientation_VERTICAL, 200.f, [](TestItem item){ return new UIButton([](){}, UIButtonStyle::defaultStyle(), EUIAlign::CENTERCENTER, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(50, 50));}, std::vector<TestItem>{TestItem{0}, TestItem{1}, TestItem{2}, TestItem{3}});

    //UIComponentSet* set = new UIComponentSet(std::vector<UIComponent*>{rect, button});
    
    //UITextBox* textBox = new UITextBox(&textVar, UITextBoxStyle::defaultStyle(*Resources::getInstance()->Font("fonts/font.ttf")), EUIAlign::TOPLEFT, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(-1.f, 0.f));
    //UIBox* box = new UIBox(sf::Vector2f(100, 100), sf::Vector2f(500, 500), new UIBorder(UIBorderStyle{sf::Color::Cyan, 5.f}, rect));
    //UICanvas* canvas = new UICanvas(sf::Vector2f(800, 800), UICanvasStyle{EUICanvasVerticalSliderPosition::RIGHT, EUICanvasHorizontalSliderPosition::BOTTOM, 10.f, 10}, rect);
    
    //UICheckbox* cb = new UICheckbox(&boolVar, UICheckboxStyle::defaultStyle(), EUIAlign::TOPLEFT, EUIFit::EUIFit_NONE, sf::Vector2f(0.f, 0.f), sf::Vector2f(400, 400));
    
    intVar = 50;

    //UISlider* sl = new UISlider(&intVar, EUISliderOrientation::EUISliderOrientation_HORIZONTAL, UISliderStyle::defaultStyle(), EUIAlign::TOPLEFT, EUIFit::EUIFit_NONE, sf::Vector2f(0.f, 0.f), sf::Vector2f(300, 100));

    //UIButtonStyle bstyle = UIButtonStyle::defaultStyle();
    //bstyle.texture = Resources::getInstance()->Texture("textures/crate.png");
    //bstyle.textureRect = std::optional<sf::IntRect>(sf::IntRect(sf::Vector2i(), sf::Vector2i(200, 100)));

    //UIButton* button = new UIButton([]{}, bstyle, EUIAlign_NONE, EUIFit_NONE, sf::Vector2f(), sf::Vector2f(200, 100));

    UIBox* box = new UIBox(sf::Vector2f(100, 100), sf::Vector2f(400, 400), new UIDivider(EUIDividerOrientation_HORIZONTAL, 150.f, new UIRect(UIRectStyle::defaultStyle(), EUIAlign_NONE, EUIFit_NONE, sf::Vector2f(), sf::Vector2f(-1.f, -1.f)), itemList));
    level.addEntity(box);

    this->box = box;

    _EntityRegistry::printTree();

    std::cout << TestEntity::snode->className << " " << Entity::snode->className << " " << PhysicEntity::snode->className << " " << Entity::isA<TestEntity>(*entity) << std::endl;
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
