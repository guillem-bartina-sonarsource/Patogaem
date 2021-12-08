
#include "UIButton.h"

#include "SFML/Graphics/RectangleShape.hpp"

UIButton::UIButton(UICallback callback, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size)
: UIComponent(align, fit, position, size, new sf::RectangleShape(size)),
callback(callback),
mouseInside(false),
buttonPressed(false)
{
    sf::RectangleShape* rect =  static_cast<sf::RectangleShape*>(getDrawable());
    rect->setFillColor(sf::Color(120, 120, 120));
    rect->setOutlineThickness(-2.f);
    rect->setOutlineColor(sf::Color(200, 200, 200));
}

UIButton::~UIButton() {}

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
                    rect->setFillColor(sf::Color(140, 140, 140));
                }
                mouseInside = true;
            }
            else
            {
                if(mouseInside and not buttonPressed)
                {
                    rect->setFillColor(sf::Color(120, 120, 120));
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
                rect->setFillColor(sf::Color(180, 180, 180));
                buttonPressed = true;
            }
            result = true;
        }
            break;
        case sf::Event::MouseButtonReleased:
        {
            if(buttonPressed)
            {
                rect->setFillColor(sf::Color(120, 120, 120));
                buttonPressed = false;
                if(mouseInside)
                {
                    callback();
                }
            }
            result = true;
        }
            break;
        case sf::Event::MouseLeft:
        {
            if(mouseInside or buttonPressed)
            {
                rect->setFillColor(sf::Color(120, 120, 120));
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
