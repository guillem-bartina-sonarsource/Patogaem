#ifndef UIRECT_HPP
#define UIRECT_HPP

#include <iostream>
#include <optional>

#include "UIComponent.h"

struct UIRectStyle
{
    sf::Texture* texture = nullptr;
    std::optional<sf::IntRect> textureRect = std::nullopt;
    sf::Color fillColor;
    float outlineThickness;
    sf::Color outlineColor;

    static UIRectStyle defaultStyle()
    {
        return {
            .fillColor = sf::Color::Magenta,
            .outlineThickness = 0.f,
            .outlineColor = sf::Color::Black
        };
    }
};

class UIRect : public UIComponent
{
    public:

    UIRect(UIRectStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position = sf::Vector2f(), const sf::Vector2f& size = sf::Vector2f(1.f, 1.f));
    ~UIRect();

    void setSize(const sf::Vector2f& size) override;

};

#endif