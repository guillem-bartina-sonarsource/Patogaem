
#include "UIBox.h"

UIBox::UIBox(const sf::Vector2f& position, const sf::Vector2f& size, UIComponent* content)
: Entity(position, size)
{
    this->content = content;
    content->setParent(this);
}

UIBox::~UIBox()
{
    if(content)
    {
        delete content;
    }
}

void UIBox::setSize(const sf::Vector2f& size)
{
    Entity::setSize(size);
    content->setParent(this); //trigger fit to parent
}

void UIBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(*content, states);
}
