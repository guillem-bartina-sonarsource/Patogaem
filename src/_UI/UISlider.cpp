
#include "UISlider.h"

#include <math.h>

#include "SFML/Graphics/RectangleShape.hpp"

UISlider::UISlider(int* bound, EUISliderOrientation orientation, UISliderStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size)
: UIComponent(align, fit, position, size, new sf::RectangleShape()),
bound(bound),
orientation(orientation),
style(style),
mouseInside(false),
mousePressed(false)
{
    *bound = std::max(*bound, style.minValue);
    *bound = std::min(*bound, style.maxValue);

    static_cast<sf::RectangleShape*>(getDrawable())->setFillColor(style.railFillColor);
}

UISlider::~UISlider() {}

void UISlider::setSize(const sf::Vector2f& size)
{
    if(orientation == EUISliderOrientation::EUISliderOrientation_HORIZONTAL)
    {
        static_cast<sf::RectangleShape*>(getDrawable())->setPosition(sf::Vector2f(0.f, size.y * 0.4f));
        static_cast<sf::RectangleShape*>(getDrawable())->setSize(sf::Vector2f(size.x, size.y * 0.2f));
    }
    else if(orientation == EUISliderOrientation::EUISliderOrientation_VERTICAL)
    {
        static_cast<sf::RectangleShape*>(getDrawable())->setPosition(sf::Vector2f(size.x * 0.4f, 0.f));
        static_cast<sf::RectangleShape*>(getDrawable())->setSize(sf::Vector2f(size.x * 0.2f, size.y));
    }

    UIComponent::setSize(size);
}

bool UISlider::handleEvents(const sf::Event& event)
{
    bool result = false;
    switch(event.type)
    {
        case sf::Event::MouseMoved:
        {
            mouseInside = isInside(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
            result = true;
        }
            break;
        case sf::Event::MouseButtonPressed:
        {
            if(mouseInside and not mousePressed)
            {
                mousePressed = true;
            }
            result = true;
        }
            break;
        case sf::Event::MouseButtonReleased:
        {
            if(mousePressed)
            {
                mousePressed = false;
                if(mouseInside)
                {
                    float ratio = 0.f;
                    if(orientation == EUISliderOrientation::EUISliderOrientation_HORIZONTAL)
                    {
                        ratio = std::min(float(event.mouseButton.x), getSize().x * 0.9f) / (getSize().x * 0.9f);
                    }
                    else if(orientation == EUISliderOrientation::EUISliderOrientation_VERTICAL)
                    {
                        ratio = std::min(float(event.mouseButton.y), getSize().y * 0.9f) / (getSize().y * 0.9f);
                    }
                    *bound = int((style.maxValue - style.minValue) * ratio);
                }
            }
            result = true;
        }
            break;
        case sf::Event::MouseLeft:
        {
            mouseInside = false;
        }
            break;
        case sf::Event::KeyPressed:
        {
            result = true;
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
                case sf::Keyboard::Right:
                    *bound = std::min(*bound+1, style.maxValue);
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::Left:
                    *bound = std::max(*bound-1, style.minValue);
                    break;
                default:
                    result = false;
                    break;
            }
        }
            break;
        case sf::Event::MouseWheelScrolled:
        {
            if(event.mouseWheelScroll.delta >= 0.f)
            {
                *bound = std::min(*bound+1, style.maxValue);
            }
            else
            {
                *bound = std::max(*bound-1, style.minValue);
            }
            result = true;
        }
            break;
        default:
            break;
    }
    return result;
}

void UISlider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    UIComponent::draw(target, states);

    sf::RectangleShape thumb;
    thumb.setFillColor(style.thumbFillColor);
    thumb.setOutlineThickness(style.thumbOutlineThickness);
    thumb.setOutlineColor(style.thumbOutlineColor);

    float ratio = *bound / float(style.maxValue - style.minValue);

    if(orientation == EUISliderOrientation::EUISliderOrientation_HORIZONTAL)
    {
        thumb.setSize(sf::Vector2f(getSize().x * 0.1f, getSize().y));
        thumb.setPosition((getSize().x * 0.9f) * ratio, 0.f);
    }
    else if(orientation == EUISliderOrientation::EUISliderOrientation_VERTICAL)
    {
        thumb.setSize(sf::Vector2f(getSize().x, getSize().y * 0.1f));
        thumb.setPosition(0.f, (getSize().y * 0.9f) * ratio);
    }

    sf::RenderStates renderStatesCopy(states);
    renderStatesCopy.transform *= getTransform();
    target.draw(thumb, renderStatesCopy);
}
