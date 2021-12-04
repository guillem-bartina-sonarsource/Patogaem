
#include "UIBorder.h"

#include "math.h"

UIBorder::UIBorder(UIBorderStyle style, UIComponent* content)
: UIComponent(EUIAlign::TOPLEFT, EUIFit::ADJUST, sf::Vector2f(), sf::Vector2f(), new sf::RectangleShape()),
thickness(style.thickness)
{
    sf::RectangleShape* rect =  static_cast<sf::RectangleShape*>(getDrawable());
    rect->setFillColor(sf::Color::Transparent);
    rect->setOutlineThickness(-abs(style.thickness));
    rect->setOutlineColor(style.color);

    inner = new UIBox(sf::Vector2f(), sf::Vector2f(), content);
}

UIBorder::~UIBorder()
{
    delete inner;
}

void UIBorder::setSize(const sf::Vector2f& size)
{
    UIComponent::setSize(size);
    static_cast<sf::RectangleShape*>(getDrawable())->setSize(size);
    inner->setPosition(sf::Vector2f(thickness, thickness));
    inner->setSize(getSize() - (sf::Vector2f(thickness, thickness) * 2.f));
}

void UIBorder::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(*getDrawable(), states);
    target.draw(*inner, states);
}
