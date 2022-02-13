
#include "UIDivider.h"

UIDivider::UIDivider(EUIDividerOrientation orientation, float partition, UIComponent* topOrLeftContent, UIComponent* bottomOrRightContent)
: UIComponent(EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(-1.f, -1.f)),
orientation(orientation),
partition(partition),
topOrLeftContent(topOrLeftContent),
bottomOrRightContent(bottomOrRightContent),
topOrLeftInner(nullptr),
bottomOrRightInner(nullptr)
{}

UIDivider::~UIDivider()
{
    if(topOrLeftInner)
    {
        delete topOrLeftInner;
    }
    if(bottomOrRightInner)
    {
        delete bottomOrRightInner;
    }
}

void UIDivider::setSize(const sf::Vector2f& size)
{
    if(topOrLeftInner)
    {
        delete topOrLeftInner;
    }
    if(bottomOrRightInner)
    {
        delete bottomOrRightInner;
    }
    sf::Vector2f offset = (orientation == EUIDividerOrientation_VERTICAL ? sf::Vector2f(size.x, partition < 0.f ? -partition * size.y : partition) : sf::Vector2f(partition < 0.f ? -partition * size.x : partition, size.y));
    topOrLeftInner = new UIBox(sf::Vector2f(), offset, topOrLeftContent);
    bottomOrRightInner = new UIBox(orientation == EUIDividerOrientation_VERTICAL ? sf::Vector2f(0.f, offset.y) : sf::Vector2f(offset.x, 0.f), orientation == EUIDividerOrientation_VERTICAL ? sf::Vector2f(size.x, size.y - offset.y) : sf::Vector2f(size.x - offset.x, size.y), bottomOrRightContent);
    UIComponent::setSize(size);
}

bool UIDivider::handleEvents(const sf::Event& event)
{
    return topOrLeftInner->handleEvents(event) or bottomOrRightInner->handleEvents(event);
}

void UIDivider::update(const sf::Time deltatime)
{
    topOrLeftInner->update(deltatime);
    bottomOrRightInner->update(deltatime);
    UIComponent::update(deltatime);
}

void UIDivider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RenderStates renderStatesCopy(states);
    renderStatesCopy.transform *= getTransform();
    target.draw(*topOrLeftInner, renderStatesCopy);
    target.draw(*bottomOrRightInner, renderStatesCopy);
}
