#ifndef UICANVAS_HPP
#define UICANVAS_HPP

#include "UIBox.h"
#include "UIComponent.h"


class UICanvas : public UIComponent
{
    public:

    UICanvas(UIComponent* content);
    ~UICanvas();

    void setParent(UIBox* parent) override;

    //void setSize(const sf::Vector2f& size) override;

    void handleEvents(const sf::Event& event) override;

    private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    UIComponent* content;

};

#endif