
#include "UICanvas.h"

UICanvas::UICanvas(UIComponent* content)
: UIComponent(EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f()),
content(content)
{}

UICanvas::~UICanvas()
{
    delete content;
}

void UICanvas::setParent(UIBox* parent)
{
    sf::Vector2f size = parent->getSize();
    UIComponent::setSize(size);
    static_cast<sf::RectangleShape*>(getDrawable())->setSize(size);
    inner = new UIBox(sf::Vector2f(offset, offset), size - (sf::Vector2f(offset, offset) * 2.f), content);
    UIComponent::setParent(parent);
}

void UICanvas::handleEvents(const sf::Event& event)
{
    inner->handleEvents(event);
}

void UICanvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(*getDrawable(), states);
    target.draw(*inner, states);
}
