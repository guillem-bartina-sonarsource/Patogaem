#ifndef UILABEL_HPP
#define UILABEL_HPP

#include "UIComponent.h"

struct UILabelStyle
{
    const sf::Font& font;
    unsigned int characterSize;
    unsigned int style;
    sf::Color fillColor;
    float outlineThickness;
    sf::Color outlineColor;

    static UILabelStyle defaultStyle(const sf::Font& font)
    {
        return {
            font,
            30,
            sf::Text::Regular,
            sf::Color::Cyan,
            0.f,
            sf::Color::Black
        };
    }
};

class UILabel : public UIComponent
{
    public:

    UILabel(const std::string& text, UILabelStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size);
    ~UILabel();

    void setSize(const sf::Vector2f& size) override;

};

#endif