#ifndef UIBOX_HPP
#define UIBOX_HPP

#include "UIComponent.h"

class UIBox : public UIComponent
{
    public:

    UIBox(const sf::Vector2f& position, const sf::Vector2f& size, UIComponent* content);
    ~UIBox();

    void levelize(Level* level) override;

    private:

    UIComponent* content;

};

#endif