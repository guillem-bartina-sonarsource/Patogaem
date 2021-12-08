#ifndef UICOMPONENT_HPP
#define UICOMPONENT_HPP

#include <functional>

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

typedef std::function<void()> UICallback;

class UIBox;

class UIComponent : public Entity
{
    public:

    UIComponent(EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size, sf::Drawable* drawable = nullptr);
    ~UIComponent();

    UIBox* getParent();
    virtual void setParent(UIBox* parent);

    virtual bool handleEvents(const sf::Event& event);

    private:

    UIBox* parent;

    EUIAlign align;
    EUIFit fit;

};

#endif