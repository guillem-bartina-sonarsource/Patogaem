
#include "UIBorder.h"

#include <math.h>

UIBorder::UIBorder(UIBorderStyle style, UIComponent* content)
: UIComponent(EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(-1.f, -1.f), new sf::RectangleShape()),
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

void UIBorder::setSize(const sf::Vector2f& size)
{
    static_cast<sf::RectangleShape*>(getDrawable())->setSize(size);
    if(inner)
    {
        delete inner;
    }
    inner = new UIBox(sf::Vector2f(offset, offset), getSize() - (sf::Vector2f(offset, offset) * 2.f), content);
    UIComponent::setSize(size);
}

bool UIBorder::handleEvents(const sf::Event& event)
{
    return inner->handleEvents(event);
}

void UIBorder::update(const sf::Time deltatime)
{
    inner->update(deltatime);
    UIComponent::update(deltatime);
}

void UIBorder::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RenderStates renderStatesCopy(states);
    renderStatesCopy.transform *= getTransform();
    target.draw(*inner, renderStatesCopy);
    
    UIComponent::draw(target, states);
}
