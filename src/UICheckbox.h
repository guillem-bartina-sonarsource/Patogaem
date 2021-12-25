#ifndef UICHECKBOX_HPP
#define UICHECKBOX_HPP

#include "UIRect.h"

struct UICheckboxStyle : public UIRectStyle
{
    sf::Color hoveringFillColor;
    sf::Color crossFillColor;
    float crossOutlineThickness;
    sf::Color crossOutlineColor;

    static UICheckboxStyle defaultStyle()
    {
        return {
            {
                sf::Color(60, 60, 60),
                -1.f,
                sf::Color(180, 180, 180)
            },
            sf::Color(120, 120, 120),
            sf::Color(220, 220, 220),
            0.f,
            sf::Color(100, 100, 100),
        };
    }
};

// Allow to wrtie text or draw a texture on the button

class UICheckbox : public UIRect
{
    public:

    // Add Style
    UICheckbox(bool* bound, UICheckboxStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size);
    ~UICheckbox();

    bool handleEvents(const sf::Event& event) override;

    protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

    sf::ConvexShape buildCross() const;

    bool* bound;

    const UICheckboxStyle style;

    bool mouseInside;
    bool checked;
};

#endif