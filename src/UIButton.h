#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include "UIComponent.h"

/*
struct UIButtonStyle
{
    sf::Color fillColor;
    float outlineThickness;
    sf::Color outlineColor;
    sf::Texture* texture = nullptr;
    std::optional<sf::IntRect> textureRect = std::nullopt;

    static UIButtonStyle defaultStyle()
    {
        return {
            .fillColor = sf::Color::Cyan,
            .outlineThickness = 0.f,
            .outlineColor = sf::Color::Black
        };
    }
};
*/

class UIButton : public UIComponent
{
    public:

    // Add Style
    UIButton(UICallback callback, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size);
    ~UIButton();

    bool handleEvents(const sf::Event& event) override;

    private:

    bool isInside(const sf::Vector2f& point);

    UICallback callback;

    bool mouseInside;
    bool buttonPressed;

};

#endif