
#include "UIButton.h"

#include "SFML/Graphics/RectangleShape.hpp"

UIButton::UIButton(UICallback callback, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size)
: UIComponent(align, fit, position, size, new sf::RectangleShape(size)),
callback(callback),
pressed(false)
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
        case sf::Event::MouseButtonPressed:
        {
            if(not pressed and rect->getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
            {
                rect->setFillColor(sf::Color(180, 180, 180));
                pressed = true;
            }
            result = true;
        }
            break;
        case sf::Event::MouseButtonReleased:
        {
            if(pressed)
            {
                rect->setFillColor(sf::Color(120, 120, 120));
                pressed = false;
                if(rect->getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                {
                    callback();
                }
            }
            result = true;
        }
            break;
        case sf::Event::MouseLeft:
        {
            if(pressed)
            {
                rect->setFillColor(sf::Color(120, 120, 120));
                pressed = false;
            }
            result = false;
        }
            break;
        default:
            break;
    }
    return result;
}
