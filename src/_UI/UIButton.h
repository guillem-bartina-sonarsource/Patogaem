#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include "UIRect.h"

struct UIButtonStyle : public UIRectStyle
{
    sf::Color hoveringFillColor;
    sf::Color clickedFillColor;

    static UIButtonStyle defaultStyle()
    {
        return {
            {
                sf::Color(60, 60, 60),
                -1.f,
                sf::Color(180, 180, 180)
            },
            sf::Color(160, 160, 160),
            sf::Color(220, 220, 220)
        };
    }
};

// Allow to wrtie text or draw a texture on the button

class UIButton : public UIRect
{
    public:

    // Add Style
    UIButton(UICallback callback, UIButtonStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size);
    ~UIButton();

    bool handleEvents(const sf::Event& event) override;

    private:

    const UIButtonStyle style;
    const UICallback callback;

    bool mouseInside;
    bool buttonPressed;

};

#endif