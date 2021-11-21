#ifndef UIRECT_HPP
#define UIRECT_HPP

#include <iostream>

#include "UIComponent.h"

class ShapeWrapper : public sf::Sprite
{
    public:

    ShapeWrapper(sf::Vector2f size) : sf::Sprite()
    {
        this->size = size;
    }

    ~ShapeWrapper() {}

    sf::Vector2f size;

    private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {   
        sf::RectangleShape frame(size);
        frame.setFillColor(sf::Color::Cyan);
        target.draw(frame, states);
    }
};

class UIRect : public UIComponent
{
    public:

    UIRect(EUIAlign align, EUIFit fit, const sf::Vector2f& position = sf::Vector2f(), const sf::Vector2f& size = sf::Vector2f(1.f, 1.f));
    ~UIRect();

    void setSize(const sf::Vector2f& size) override;

    private:

    ShapeWrapper* ref;

};

#endif