
#include "UIRect.h"

UIRect::UIRect(EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size)
: UIComponent(align, fit, position, size, new ShapeWrapper(size))
{
    setPosition(position);
    ref = static_cast<ShapeWrapper*>(getSprite());
}

UIRect::~UIRect() {}

void UIRect::setSize(const sf::Vector2f& size)
{
    ref->size = size;
    UIComponent::setSize(size);
}