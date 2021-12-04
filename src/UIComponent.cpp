
#include "UIComponent.h"

#include "UIBox.h"

UIComponent::UIComponent(EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size, sf::Drawable* drawable)
: Entity(position, size, drawable),
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

    this->parent = parent;
}

void UIComponent::handleEvents(const sf::Event& event) {}
