
#include "UICanvas.h"

#include <math.h>

#include "UIRect.h"

UICanvas::UICanvas(const sf::Vector2f& size, UICanvasStyle style, UIComponent* content)
: UIComponent(EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f()),
size(size),
style(style),
content(content),
inner(nullptr),
offset(sf::Vector2f()),
maxOffset(sf::Vector2f()),
canvas(nullptr)
{}

UICanvas::~UICanvas() {}

void UICanvas::setParent(UIBox* parent)
{
    if(inner or canvas)
    {
        delete inner;
        delete canvas;
    }
    sf::Vector2f parentSize = parent->getSize();
    UIComponent::setSize(parentSize);

    bool verticalSlider = size.y > parentSize.y;
    bool horizontalSlider = size.x > parentSize.x;

    sf::Vector2f boxPosition = sf::Vector2f(int(verticalSlider) * int(style.verticalSliderPosition == EUICanvasVerticalSliderPosition::LEFT) * style.sliderThickness, int(horizontalSlider) * int(style.horizontalSliderPosition == EUICanvasHorizontalSliderPosition::TOP) * style.sliderThickness);
    sf::Vector2f boxSize = sf::Vector2f(std::min(size.x, parentSize.x - style.sliderThickness * int(verticalSlider) * int(style.verticalSliderPosition > 0)), std::min(size.y, parentSize.y - style.sliderThickness * int(horizontalSlider) * int(style.horizontalSliderPosition > 0)));

    canvas = new UIBox(sf::Vector2f(), size, content);
    inner = new UIBox(boxPosition, boxSize, canvas);

    maxOffset = size - boxSize;

    UIComponent::setParent(parent);
}

void UICanvas::handleEvents(const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Up:
                    tryMove(EUICanvasDirection::DIR_UP);
                    break;
                case sf::Keyboard::Down:
                    tryMove(EUICanvasDirection::DIR_DOWN);
                    break;
                case sf::Keyboard::Left:
                    tryMove(EUICanvasDirection::DIR_LEFT);
                    break;
                case sf::Keyboard::Right:
                    tryMove(EUICanvasDirection::DIR_RIGHT);
                    break;
                default:
                    break;
            }
        }
            break;
        case sf::Event::MouseWheelScrolled:
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) or sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
            {
                if(event.mouseWheelScroll.delta >= 0.f)
                {
                    tryMove(EUICanvasDirection::DIR_LEFT);
                }
                else
                {
                    tryMove(EUICanvasDirection::DIR_RIGHT);
                }
            }
            else
            {
                if(event.mouseWheelScroll.delta >= 0.f)
                {
                    tryMove(EUICanvasDirection::DIR_UP);
                }
                else
                {
                    tryMove(EUICanvasDirection::DIR_DOWN);
                }
            }
        }
            break;
        default:
            break;
    }
    //inner->handleEvents(event);
}

void UICanvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(*inner, states);
}

void UICanvas::tryMove(EUICanvasDirection direction)
{
    switch(direction)
    {
        case EUICanvasDirection::DIR_UP:
        {
            if(offset.y > 0.f)
            {
                offset.y -= style.scrollSensitivity;
            }
        }
            break;
        case EUICanvasDirection::DIR_DOWN:
        {
            if(offset.y < maxOffset.y)
            {
                offset.y += style.scrollSensitivity;
            }
        }
            break;
        case EUICanvasDirection::DIR_LEFT:
        {
            if(offset.x > 0.f)
            {
                offset.x -= style.scrollSensitivity;
            }
        }
            break;
        case EUICanvasDirection::DIR_RIGHT:
        {
            if(offset.x < maxOffset.x)
            {
                offset.x += style.scrollSensitivity;
            }
        }
            break;
        default:
            break;
    }
    canvas->setPosition(-offset);
}


