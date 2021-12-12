
#include "UIBox.h"

#include <iostream>

UIBox::UIBox(const sf::Vector2f& position, const sf::Vector2f& size, UIComponent* content)
: UIComponent(EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, position, size, new sf::RectangleShape()),
content(content),
isMouseInside(false)
{
    renderTexture.create(size.x, size.y);
    sf::RectangleShape* rect = static_cast<sf::RectangleShape*>(getDrawable());
    rect->setSize(size);
    rect->setTextureRect(sf::IntRect(0, size.y, size.x, -size.y));
    rect->setTexture(&renderTexture.getTexture());
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
    renderTexture.create(size.x, size.y);
    sf::RectangleShape* rect = static_cast<sf::RectangleShape*>(getDrawable());
    rect->setSize(size);
    rect->setTextureRect(sf::IntRect(0, size.y, size.x, -size.y));
    rect->setTexture(&renderTexture.getTexture());
    content->setParent(this); //trigger fit to parent
}

bool UIBox::handleEvents(const sf::Event& event)
{
    bool result = false;
    if(isMouseInside or event.type == sf::Event::MouseMoved)
    {
        switch(event.type)
        {
            case sf::Event::MouseMoved:
            {
                if(isInside(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                {
                    if(not isMouseInside)
                    {
                        sf::Event mouseEntered;
                        mouseEntered.type = sf::Event::MouseEntered;
                        result = content->handleEvents(mouseEntered);
                    }
                    sf::Event mouseMoved(event);
                    mouseMoved.mouseMove.x -= getPosition().x;
                    mouseMoved.mouseMove.y -= getPosition().y;
                    result = result or content->handleEvents(mouseMoved);
                    isMouseInside = true;
                }
                else
                {
                    if(isMouseInside)
                    {
                        sf::Event mouseLeft;
                        mouseLeft.type = sf::Event::MouseLeft;
                        result = content->handleEvents(mouseLeft);
                    }
                    isMouseInside = false;
                }
            }
                break;
            case sf::Event::MouseWheelScrolled:
            {
                sf::Event mouseWheelScrolled(event);
                mouseWheelScrolled.mouseWheelScroll.x -= getPosition().x;
                mouseWheelScrolled.mouseWheelScroll.y -= getPosition().y;
                result = content->handleEvents(mouseWheelScrolled);
            }
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
            {
                sf::Event mouseButton(event);
                mouseButton.mouseButton.x -= getPosition().x;
                mouseButton.mouseButton.y -= getPosition().y;
                result = content->handleEvents(mouseButton);
            }
                break;
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
            case sf::Event::TextEntered:
            {
                result = content->handleEvents(event);
            }
                break;
            case sf::Event::MouseLeft: //???, Why not entered?
            {
                result = content->handleEvents(event);
                isMouseInside = false;
            }
                break;
            default:
                break;
            // TODO: Add support for joysticks
        }
    }
    return result;
}

void UIBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    renderTexture.clear();
    renderTexture.draw(*content, sf::RenderStates::Default);

    Entity::draw(target, states);
}
