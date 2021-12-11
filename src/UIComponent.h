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

    sf::Vector2f getSize() const override;

    UIBox* getParent();
    virtual void setParent(UIBox* parent);

    virtual bool handleEvents(const sf::Event& event);

    private:

    UIBox* parent;

    EUIAlign align;
    EUIFit fit;

};


class UIComponentSet : public UIComponent
{
    public:

    UIComponentSet(const std::vector<UIComponent*>& components);
    ~UIComponentSet();

    void setParent(UIBox* parent) override;

    bool handleEvents(const sf::Event& event) override;

    private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::vector<UIComponent*> components;

};

#endif