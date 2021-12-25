
#include "UICheckbox.h"

#include <math.h>

#include "SFML/Graphics/ConvexShape.hpp"

UICheckbox::UICheckbox(bool* bound, UICheckboxStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size)
: UIRect(style, align, fit, position, size),
bound(bound),
style(style),
mouseInside(false),
checked(false)
{}

UICheckbox::~UICheckbox() {}

bool UICheckbox::handleEvents(const sf::Event& event)
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
                if(mouseInside)
                {
                    rect->setFillColor(sf::Color(style.fillColor));
                }
                mouseInside = false;
            }
            result = true;
        }
            break;
        case sf::Event::MouseButtonReleased:
        {
            if(mouseInside)
            {
                checked = !checked;
            }
            result = true;
        }
            break;
        case sf::Event::MouseLeft:
        {
            if(mouseInside)
            {
                rect->setFillColor(style.fillColor);
                mouseInside = false;
            }
            result = false;
        }
            break;
        default:
            break;
    }
    return result;
}

void UICheckbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    UIRect::draw(target, states);
    if(checked)
    {
        sf::RenderStates renderStatesCopy(states);
        renderStatesCopy.transform *= getTransform();
        target.draw(buildCross(), renderStatesCopy);
    }
}

sf::ConvexShape UICheckbox::buildCross() const
{
    sf::ConvexShape cross(12);
    cross.setFillColor(style.crossFillColor);
    cross.setOutlineThickness(style.crossOutlineThickness);
    cross.setOutlineColor(style.crossOutlineColor);

    sf::Vector2f points[12] = {
        sf::Vector2f(0.5f, 0.4f),

        sf::Vector2f(0.9f, 0.05f),
        sf::Vector2f(0.95f, 0.1f),

        sf::Vector2f(0.6f, 0.5f),

        sf::Vector2f(0.95f, 0.9f),
        sf::Vector2f(0.9f, 0.95f),

        sf::Vector2f(0.5f, 0.6f),

        sf::Vector2f(0.1f, 0.95f),
        sf::Vector2f(0.05f, 0.9f),

        sf::Vector2f(0.4f, 0.5f),

        sf::Vector2f(0.05f, 0.1f),
        sf::Vector2f(0.1f, 0.05f)
    };

    sf::Vector2f size = getSize();

    for(int i = 0; i < 12; i++)
    {
        cross.setPoint(i, sf::Vector2f(points[i].x * size.x, points[i].y * size.y));
    }

    return cross;
}
