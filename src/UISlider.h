#ifndef UISLIDER_HPP
#define UISLIDER_HPP

#include "UIComponent.h"

enum EUISliderOrientation
{
    EUISliderOrientation_VERTICAL,
    EUISliderOrientation_HORIZONTAL
};

struct UISliderStyle
{
    int minValue;
    int maxValue;
    sf::Color railFillColor;
    sf::Color thumbFillColor;
    float thumbOutlineThickness;
    sf::Color thumbOutlineColor;

    static UISliderStyle defaultStyle(int maxValue = 100, int minValue = 0)
    {
        return {
            minValue,
            maxValue,
            sf::Color(60, 60, 60),
            sf::Color(180, 180, 180),
            -1.f,
            sf::Color(200, 200, 200)
        };
    }
};

class UISlider : public UIComponent
{
    public:

    UISlider(int* bound, EUISliderOrientation orientation,  UISliderStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size);
    ~UISlider();

    void setSize(const sf::Vector2f& size) override;

    bool handleEvents(const sf::Event& event) override;

    protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

    int* bound;

    const EUISliderOrientation orientation;
    const UISliderStyle style;

    bool mouseInside;
    bool mousePressed;

};

#endif