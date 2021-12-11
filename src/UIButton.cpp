
#include "UIButton.h"

#include <math.h>

#include "SFML/Graphics/RectangleShape.hpp"

UIButton::UIButton(UIButtonStyle style, UICallback callback, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size)
: UIComponent(align, fit, position, size, new sf::RectangleShape(size)),
style(style),
callback(callback),
mouseInside(false),
buttonPressed(false)
{
    sf::RectangleShape* rect =  static_cast<sf::RectangleShape*>(getDrawable());
    rect->setFillColor(style.fillColor);
    rect->setOutlineThickness(-abs(style.outlineThickness));
    rect->setOutlineColor(style.outlineColor);
}

UIButton::~UIButton() {}

void UIButton::setSize(const sf::Vector2f& size)
{
    static_cast<sf::RectangleShape*>(getDrawable())->setSize(size);
    UIComponent::setSize(size);
}

bool UIButton::handleEvents(const sf::Event& event)
{
    bool result = false;
    sf::RectangleShape* rect = static_cast<sf::RectangleShape*>(getDrawable());
    switch(event.type)
    {
        case sf::Event::MouseMoved:
        {
            if(isInside(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
            {
                if(not mouseInside)
                {
                    rect->setFillColor(sf::Color(style.hoveringFillColor));
                }
                mouseInside = true;
            }
            else
            {
                if(mouseInside and not buttonPressed)
                {
                    rect->setFillColor(sf::Color(style.fillColor));
                }
                mouseInside = false;
            }
            result = true;
        }
            break;
        case sf::Event::MouseButtonPressed:
        {
            if(mouseInside and not buttonPressed)
            {
                rect->setFillColor(style.clickedFillColor);
                buttonPressed = true;
            }
            result = true;
        }
            break;
        case sf::Event::MouseButtonReleased:
        {
            if(buttonPressed)
            {
                buttonPressed = false;
                if(mouseInside)
                {
                    callback();
                    rect->setFillColor(style.hoveringFillColor);
                }
                else
                {
                    rect->setFillColor(style.fillColor);
                }
            }
            result = true;
        }
            break;
        case sf::Event::MouseLeft:
        {
            if(mouseInside or buttonPressed)
            {
                rect->setFillColor(style.fillColor);
                mouseInside = false;
                buttonPressed = false;
            }
            result = false;
        }
            break;
        default:
            break;
    }
    return result;
}

bool UIButton::isInside(const sf::Vector2f& point)
{
    return (point.x >= getPosition().x) and (point.x <= getPosition().x + getSize().x * getScale().x) and (point.y >= getPosition().y) and (point.y <= getPosition().y + getSize().y * getScale().y);
}
