#ifndef UIRECT_HPP
#define UIRECT_HPP

#include <optional>

#include "UIComponent.h"

struct UIRectStyle
{
    sf::Color fillColor;
    float outlineThickness;
    sf::Color outlineColor;
    sf::Texture* texture = nullptr;
    std::optional<sf::IntRect> textureRect = std::nullopt;

    static UIRectStyle defaultStyle()
    {
        return {
            .fillColor = sf::Color::Cyan,
            .outlineThickness = 0.f,
            .outlineColor = sf::Color::Black
        };
    }
};

class UIRect : public UIComponent
{
    public:

    UIRect(UIRectStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size);
    ~UIRect();

    void setSize(const sf::Vector2f& size) override;

};

#endif