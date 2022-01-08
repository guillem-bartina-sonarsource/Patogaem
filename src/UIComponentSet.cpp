
#include "UIComponentSet.h"

#include <ranges>


UIComponentSet::UIComponentSet(const std::vector<UIComponent*>& components, bool ordered)
: UIComponent(EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f()),
components(components),
ordered(ordered)
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
        if(not ordered or not result)
        {
            bool x = component->handleEvents(event);
            result = result or x;
        }
    }

    return result;
}

void UIComponentSet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for(UIComponent* const& component : components | std::views::reverse)
    {
        target.draw(*component, states);
    }
}


