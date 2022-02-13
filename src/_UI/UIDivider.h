#ifndef UIDIVIDER_HPP
#define UIDIVIDER_HPP

#include "UIComponent.h"
#include "UIBox.h"

enum EUIDividerOrientation
{
    EUIDividerOrientation_VERTICAL,
    EUIDividerOrientation_HORIZONTAL
};

class UIDivider : public UIComponent
{
    public:

    UIDivider(EUIDividerOrientation orientation, float partition, UIComponent* topOrLeftContent, UIComponent* bottomOrRightContent);
    ~UIDivider();

    void setSize(const sf::Vector2f& size) override;

    bool handleEvents(const sf::Event& event) override;

    void update(const sf::Time deltatime) override;

    protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

    const EUIDividerOrientation orientation;
    const float partition;

    UIComponent* topOrLeftContent;
    UIComponent* bottomOrRightContent;

    UIBox* topOrLeftInner;
    UIBox* bottomOrRightInner;
};

#endif