
#include "UIComponent.h"

#include "UIBox.h"

UIComponent::UIComponent(EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size, sf::Sprite* sprite)
: Entity(position, size, sprite),
align(align),
fit(fit),
parent(nullptr) {}

UIComponent::~UIComponent() {}

UIBox* UIComponent::getParent()
{
    return parent;
}

void UIComponent::setParent(UIBox* parent)
{
    float ratio = 1.f;
    switch(fit)
    {
    case EUIFit::HORIZONTAL:
        ratio = getSize().y / getSize().x;
        setSize(sf::Vector2f(parent->getSize().x, parent->getSize().x * ratio));
        break;
    case EUIFit::VERTICAL:
        ratio = getSize().y / getSize().x;
        setSize(sf::Vector2f(parent->getSize().y / ratio, parent->getSize().y));
        break;
    case EUIFit::ADJUST:
        setSize(parent->getSize());
    case EUIFit::MAX:
        ratio = getSize().y / getSize().x;
        if(ratio <= 1.f)
        {
            setSize(sf::Vector2f(parent->getSize().x, parent->getSize().x * ratio));
        }
        else
        {
            setSize(sf::Vector2f(parent->getSize().y / ratio, parent->getSize().y));
        }
    default:
        break;
    }

    sf::Vector2f sizeDiff = parent->getSize() - getSize();

    if(align != EUIAlign::EUIAlign_NONE)
    {
        setPosition(parent->getPosition() + sf::Vector2f(sizeDiff.x * ((align-1) % 3), sizeDiff.y * ((align-1) / 3)) * 0.5f);
    }

    this->parent = parent;
}
