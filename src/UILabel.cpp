
#include "UILabel.h"

#include <iostream>

#include "SFML/Graphics/Text.hpp"

UILabel::UILabel(const std::string& text, UILabelStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size)
: UIComponent(align, fit, position, size, new sf::Text())
{
    sf::Text* label =  static_cast<sf::Text*>(getDrawable());
    label->setString(text);
    label->setFont(style.font);
    label->setCharacterSize(style.characterSize);
    label->setStyle(style.style);
    label->setFillColor(style.fillColor);
    label->setOutlineThickness(style.outlineThickness);
    label->setOutlineColor(style.outlineColor);
    sf::FloatRect textLocalBounds = label->getLocalBounds();
    UIComponent::setSize(sf::Vector2f(textLocalBounds.width, textLocalBounds.height));
}

UILabel::~UILabel() {}

void UILabel::setSize(const sf::Vector2f& size)
{
    sf::Vector2f prevSize = getSize();
    UIComponent::setSize(size);
    //std::cout << "SCALING" << sf::Vector2f(size.x / prevSize.x, size.y / prevSize.y).x << " " << sf::Vector2f(prevSize.x / size.x, prevSize.y / size.y).y << std::endl;
    static_cast<sf::Text*>(getDrawable())->setScale(sf::Vector2f(size.x / prevSize.x, size.y / prevSize.y));
}
