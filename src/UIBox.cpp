
#include "UIBox.h"

UIBox::UIBox(const sf::Vector2f& position, const sf::Vector2f& size, UIComponent* content)
: UIComponent(EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, position, size)
{
    content->setParent(this);
    this->content = content;
}

UIBox::~UIBox()
{
    if(content)
    {
        delete content;
    }
}

void UIBox::levelize(Level* level)
{
    UIComponent::levelize(level);
    content->levelize(level);
}