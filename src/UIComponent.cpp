
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

bool UIComponent::handleEvents(const sf::Event& event)
{
    return false;
}


UIComponentSet::UIComponentSet(const std::vector<UIComponent*>& components)
: UIComponent(EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f()),
components(components)
{}

UIComponentSet::~UIComponentSet()
{
    for(UIComponent*& component : components)
    {
        delete component;
    }
}

void UIComponentSet::setParent(UIBox* parent)
{
    for(UIComponent*& component : components)
    {
        component->setParent(parent);
    }
}

bool UIComponentSet::handleEvents(const sf::Event& event)
{
    bool result = false;

    for(UIComponent*& component : components)
    {
        bool x = component->handleEvents(event);
        result = result or x;
    }

    return result;
}

void UIComponentSet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for(UIComponent* const& component : components)
    {
        target.draw(*component, states);
    }
}


