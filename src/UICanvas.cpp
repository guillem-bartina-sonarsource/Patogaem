
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
verticalSlider(false),
horizontalSlider(false),
showVerticalSlider(false),
showHorizontalSlider(false),
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

    verticalSlider = size.y > parentSize.y;
    horizontalSlider = size.x > parentSize.x;

    showVerticalSlider = verticalSlider and style.verticalSliderPosition != EUICanvasVerticalSliderPosition::EUICanvasVerticalSliderPosition_NONE;
    showHorizontalSlider = horizontalSlider and style.horizontalSliderPosition != EUICanvasHorizontalSliderPosition::EUICanvasHorizontalSliderPosition_NONE;

    sf::Vector2f boxPosition = sf::Vector2f(int(verticalSlider) * int(style.verticalSliderPosition == EUICanvasVerticalSliderPosition::LEFT) * style.sliderThickness, int(horizontalSlider) * int(style.horizontalSliderPosition == EUICanvasHorizontalSliderPosition::TOP) * style.sliderThickness);
    sf::Vector2f boxSize = sf::Vector2f(std::min(size.x, parentSize.x - style.sliderThickness * int(showVerticalSlider)), std::min(size.y, parentSize.y - style.sliderThickness * int(showHorizontalSlider)));

    canvas = new UIBox(sf::Vector2f(), size, content);
    inner = new UIBox(boxPosition, boxSize, canvas);

    maxOffset = size - boxSize;

    UIComponent::setParent(parent);
}

bool UICanvas::handleEvents(const sf::Event& event)
{
    bool result = false;
    if(not inner->handleEvents(event))
    {
        switch(event.type)
        {
            case sf::Event::KeyPressed:
            {
                result = true;
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
                        result = false;
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
                result = true;
            }
                break;
            default:
                break;
        }
    }
    return result;
}

void UICanvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(*inner, states);

    if(showVerticalSlider)
    {
        sf::RectangleShape verticalSlider(sf::Vector2f(style.sliderThickness, inner->getSize().y));
        verticalSlider.setFillColor(sf::Color::White);
        verticalSlider.setPosition(sf::Vector2f(int(style.verticalSliderPosition == EUICanvasVerticalSliderPosition::RIGHT) * (getSize().x - style.sliderThickness), inner->getPosition().y));
        target.draw(verticalSlider, states);

        sf::RectangleShape verticalThumb(sf::Vector2f(style.sliderThickness, (inner->getSize().y * inner->getSize().y / size.y)));
        verticalThumb.setFillColor(sf::Color(140, 140, 140));
        verticalThumb.setOutlineThickness(-1.f);
        verticalThumb.setOutlineColor(sf::Color(200, 200, 200));
        verticalThumb.setPosition(sf::Vector2f(int(style.verticalSliderPosition == EUICanvasVerticalSliderPosition::RIGHT) * (getSize().x - style.sliderThickness), inner->getPosition().y + (inner->getSize().y - verticalThumb.getSize().y) * (offset.y / maxOffset.y)));
        target.draw(verticalThumb, states);
    }

    if(showHorizontalSlider)
    {
        sf::RectangleShape horizontalSlider(sf::Vector2f(inner->getSize().x, style.sliderThickness));
        horizontalSlider.setFillColor(sf::Color::White);
        horizontalSlider.setPosition(sf::Vector2f(inner->getPosition().x, int(style.horizontalSliderPosition == EUICanvasHorizontalSliderPosition::BOTTOM) * (getSize().y - style.sliderThickness)));
        target.draw(horizontalSlider, states);

        sf::RectangleShape horizontalThumb(sf::Vector2f((inner->getSize().x * inner->getSize().x / size.x), style.sliderThickness));
        horizontalThumb.setFillColor(sf::Color(140, 140, 140));
        horizontalThumb.setOutlineThickness(-1.f);
        horizontalThumb.setOutlineColor(sf::Color(200, 200, 200));
        horizontalThumb.setPosition(sf::Vector2f(inner->getPosition().x + (inner->getSize().x - horizontalThumb.getSize().x) * (offset.x / maxOffset.x), int(style.horizontalSliderPosition == EUICanvasHorizontalSliderPosition::BOTTOM) * (getSize().y - style.sliderThickness)));
        target.draw(horizontalThumb, states);
    }

    if(showVerticalSlider and showHorizontalSlider)
    {
        sf::RectangleShape corner(sf::Vector2f(style.sliderThickness, style.sliderThickness));
        corner.setFillColor(sf::Color(140, 140, 140));
        corner.setPosition(sf::Vector2f(int(style.verticalSliderPosition == EUICanvasVerticalSliderPosition::RIGHT) * (getSize().x - style.sliderThickness), int(style.horizontalSliderPosition == EUICanvasHorizontalSliderPosition::BOTTOM) * (getSize().y - style.sliderThickness)));
        target.draw(corner, states);
    }
}

void UICanvas::tryMove(EUICanvasDirection direction)
{
    switch(direction)
    {
        case EUICanvasDirection::DIR_UP:
        {
            if(verticalSlider and offset.y > 0.f)
            {
                offset.y -= style.scrollSensitivity;
            }
        }
            break;
        case EUICanvasDirection::DIR_DOWN:
        {
            if(verticalSlider and offset.y < maxOffset.y)
            {
                offset.y += style.scrollSensitivity;
            }
        }
            break;
        case EUICanvasDirection::DIR_LEFT:
        {
            if(horizontalSlider and offset.x > 0.f)
            {
                offset.x -= style.scrollSensitivity;
            }
        }
            break;
        case EUICanvasDirection::DIR_RIGHT:
        {
            if(horizontalSlider and offset.x < maxOffset.x)
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


