
#include "UIComponent.h"

#include "UIBox.h"

UIComponent::UIComponent(EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size, sf::Drawable* drawable)
: Entity(position, size, drawable),
parent(nullptr),
align(align),
fit(fit)
{}

UIComponent::~UIComponent() {}

sf::Vector2f UIComponent::getSize() const
{
    sf::Vector2f size(Entity::getSize());
    if(parent)
    {
        if(size.x == -1.f)
        {
            size.x = parent->getSize().x;
        }
        if(size.y == -1.f)
        {
            size.y = parent->getSize().y;
        }
    }
    return size;
}

UIBox* UIComponent::getParent()
{
    return parent;
}

void UIComponent::setParent(UIBox* parent)
{
    this->parent = parent;

    setSize(getSize());

    float scale = 1.f;
    switch(fit)
    {
        case EUIFit::HORIZONTAL:
            scale = parent->getSize().x / getSize().x;
            setScale(scale, scale);
            break;
        case EUIFit::VERTICAL:
            scale = parent->getSize().y / getSize().y;
            setScale(scale, scale);
            break;
        case EUIFit::ADJUST:
            setScale(parent->getSize().x / getSize().x, parent->getSize().y / getSize().y);
            break;
        case EUIFit::MAX:
            if(getSize().y / getSize().x <= 1.f)
            {
                scale = parent->getSize().x / getSize().x;
                setScale(scale, scale);
            }
            else
            {
                scale = parent->getSize().y / getSize().y;
                setScale(scale, scale);
            }
            break;
        default:
            break;
    }

    sf::Vector2f sizeDiff = parent->getSize() - sf::Vector2f(getSize().x * getScale().x, getSize().y * getScale().y);

    if(align != EUIAlign::EUIAlign_NONE)
    {
        setPosition(sf::Vector2f(sizeDiff.x * ((align-1) % 3), sizeDiff.y * ((align-1) / 3)) * 0.5f);
    }
}

bool UIComponent::handleEvents(const sf::Event& event)
{
    return false;
}

bool UIComponent::isInside(const sf::Vector2f& point)
{
    return (point.x >= getPosition().x) and (point.x <= getPosition().x + getSize().x * getScale().x) and (point.y >= getPosition().y) and (point.y <= getPosition().y + getSize().y * getScale().y);
}
