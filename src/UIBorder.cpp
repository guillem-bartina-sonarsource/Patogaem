
#include "UIBorder.h"

#include "math.h"

UIBorder::UIBorder(UIBorderStyle style, UIComponent* content)
: UIComponent(EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(), new sf::RectangleShape()),
content(content),
offset(style.thickness + style.padding),
inner(nullptr)
{
    sf::RectangleShape* rect =  static_cast<sf::RectangleShape*>(getDrawable());
    rect->setFillColor(sf::Color::Transparent);
    rect->setOutlineThickness(-abs(style.thickness));
    rect->setOutlineColor(style.color);
}

UIBorder::~UIBorder()
{
    delete inner;
}

void UIBorder::setParent(UIBox* parent)
{
    sf::Vector2f size = parent->getSize();
    UIComponent::setSize(size);
    static_cast<sf::RectangleShape*>(getDrawable())->setSize(size);
    inner = new UIBox(sf::Vector2f(offset, offset), size - (sf::Vector2f(offset, offset) * 2.f), content);
    UIComponent::setParent(parent);
}

void UIBorder::handleEvents(const sf::Event& event)
{
    inner->handleEvents(event);
}

void UIBorder::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(*getDrawable(), states);
    target.draw(*inner, states);
}
