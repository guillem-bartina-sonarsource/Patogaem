#ifndef UIBORDER_HPP
#define UIBORDER_HPP

#include "UIBox.h"
#include "UIComponent.h"

struct UIBorderStyle
{
    sf::Color color;
    float thickness;
    float padding = 0.f;

    static UIBorderStyle defaultStyle()
    {
        return {
            .color = sf::Color::White,
            .thickness = 1.f
        };
    }
};

class UIBorder : public UIComponent
{
    public:

    UIBorder(UIBorderStyle style, UIComponent* content);
    ~UIBorder();

    void setSize(const sf::Vector2f& size) override;

    bool handleEvents(const sf::Event& event) override;

    private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    UIComponent* content;

    float offset;

    UIBox* inner;

};

#endif