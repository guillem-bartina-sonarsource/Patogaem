#ifndef UIBOX_HPP
#define UIBOX_HPP

#include "Entity.h"
#include "UIComponent.h"

class UIBox : public Entity
{
    public:

    UIBox(const sf::Vector2f& position, const sf::Vector2f& size, UIComponent* content);
    ~UIBox();

    void setSize(const sf::Vector2f& size) override;

    private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    UIComponent* content;
    
};

#endif