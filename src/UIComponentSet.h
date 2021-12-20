#ifndef UICOMPONENTSET_HPP
#define UICOMPONENTSET_HPP

#include "UIComponent.h"


class UIComponentSet : public UIComponent
{
    public:

    UIComponentSet(const std::vector<UIComponent*>& components);
    ~UIComponentSet();

    void setParent(UIBox* parent) override;

    bool handleEvents(const sf::Event& event) override;

    protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

    std::vector<UIComponent*> components;

};

#endif