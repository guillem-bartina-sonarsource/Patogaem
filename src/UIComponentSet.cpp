
#include "UIComponentSet.h"


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


