#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include "UIComponent.h"

struct UIButtonStyle
{
    sf::Color fillColor;
    sf::Color hoveringFillColor;
    sf::Color clickedFillColor;
    float outlineThickness;
    sf::Color outlineColor;

    static UIButtonStyle defaultStyle()
    {
        return {
            .fillColor = sf::Color(100, 0, 0),
            .hoveringFillColor = sf::Color(160, 0, 0),
            .clickedFillColor = sf::Color(220, 0, 0),
            .outlineThickness = 1.f,
            .outlineColor = sf::Color(255, 0, 0)
        };
    }
};

class UIButton : public UIComponent
{
    public:

    // Add Style
    UIButton(UIButtonStyle style, UICallback callback, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size);
    ~UIButton();

    bool handleEvents(const sf::Event& event) override;

    private:

    bool isInside(const sf::Vector2f& point);

    UIButtonStyle style;
    UICallback callback;

    bool mouseInside;
    bool buttonPressed;

};

#endif