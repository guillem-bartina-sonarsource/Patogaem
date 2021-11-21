#ifndef UICOMPONENT_HPP
#define UICOMPONENT_HPP

#include "Entity.h"

enum EUIAlign
{
    EUIAlign_NONE = 0,
    TOPLEFT,
    TOPCENTER,
    TOPRIGHT,
    CENTERLEFT,
    CENTERCENTER,
    CENTERRIGHT,
    BOTTOMLEFT,
    BOTTOMCENTER,
    BOTTOMRIGHT
};

enum EUIFit
{
    EUIFit_NONE = 0,
    HORIZONTAL,
    VERTICAL,
    ADJUST,
    MAX
};

class UIBox;

class UIComponent : public Entity
{
    public:

    UIComponent(EUIAlign align, EUIFit fit, const sf::Vector2f& position = sf::Vector2f(), const sf::Vector2f& size = sf::Vector2f(1.f, 1.f), sf::Sprite* sprite = nullptr);
    ~UIComponent();

    UIBox* getParent();
    void setParent(UIBox* parent);
    
    private:

    UIBox* parent;

    EUIAlign align;
    EUIFit fit;

};

#endif