
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
    UIComponent::setSize(sf::Vector2f(textLocalBounds.width, style.characterSize));
}

UILabel::~UILabel() {}

void UILabel::setSize(const sf::Vector2f& size)
{
    std::cerr << "UILabel::setSize has no effect" << std::endl;
}
