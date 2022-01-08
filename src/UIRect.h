#ifndef UIRECT_HPP
#define UIRECT_HPP

#include <optional>

#include "UIComponent.h"

struct UIRectStyle
{
    sf::Color fillColor;
    float outlineThickness;
    sf::Color outlineColor;
    const sf::Texture* texture = nullptr;
    std::optional<sf::IntRect> textureRect = std::nullopt;

    static UIRectStyle defaultStyle()
    {
        return {
            sf::Color::Magenta,
            0.f,
            sf::Color::Black
        };
    }
};

class UIRect : public UIComponent
{
    public:

    UIRect(UIRectStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size);
    ~UIRect();

    void setSize(const sf::Vector2f& size) override;

    void setFillColor(const sf::Color& fillColor);

};

#endif