
#include "UIBox.h"

UIBox::UIBox(const sf::Vector2f& position, const sf::Vector2f& size, UIComponent* content)
: Entity(position, size)
{
    this->content = content;
    content->setParent(this);
    mouseInside = false;
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

void UIBox::handleEvents(const sf::Event& event)
{
    if(mouseInside or event.type == sf::Event::MouseMoved)
    {
        switch(event.type)
        {
            case sf::Event::MouseMoved:
            {
                if(isInside(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                {
                    if(not mouseInside)
                    {
                        sf::Event mouseEntered;
                        mouseEntered.type = sf::Event::MouseEntered;
                        content->handleEvents(mouseEntered);
                    }
                    sf::Event mouseMoved(event);
                    mouseMoved.mouseMove.x -= getPosition().x;
                    mouseMoved.mouseMove.y -= getPosition().y;
                    content->handleEvents(mouseMoved);
                    mouseInside = true;
                }
                else
                {
                    if(mouseInside)
                    {
                        sf::Event mouseLeft;
                        mouseLeft.type = sf::Event::MouseLeft;
                        content->handleEvents(mouseLeft);
                    }
                    mouseInside = false;
                }
            }
                break;
            case sf::Event::MouseWheelScrolled:
            {
                sf::Event mouseWheelScrolled(event);
                mouseWheelScrolled.mouseWheelScroll.x -= getPosition().x;
                mouseWheelScrolled.mouseWheelScroll.y -= getPosition().y;
                content->handleEvents(mouseWheelScrolled);
            }
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
            {
                sf::Event mouseButton(event);
                mouseButton.mouseButton.x -= getPosition().x;
                mouseButton.mouseButton.y -= getPosition().y;
                content->handleEvents(mouseButton);
            }
                break;
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
            case sf::Event::TextEntered:
            {
                content->handleEvents(event);
            }
                break;
            default:
                break;

            // TODO: Add support for joysticks
        }
    }
}

void UIBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RenderTexture renderTexture;
    renderTexture.create(getSize().x, getSize().y);

    sf::Transform newTransform(getTransform());
    newTransform.translate(getPosition() * -1.f);
    sf::RenderStates statesCopy(states);
    renderTexture.clear();
    renderTexture.draw(*content, newTransform);

    sf::RectangleShape rect(getSize());
    rect.setTexture(&renderTexture.getTexture());

    states.transform *= getTransform();
    target.draw(rect, states);

    /*
    states.transform *= getTransform();
    target.draw(*content, states);
    */
}

bool UIBox::isInside(const sf::Vector2f& point)
{
    return (point.x >= getPosition().x) and (point.x <= getPosition().x + getSize().x) and (point.y >= getPosition().y) and (point.y <= getPosition().y + getSize().y);
}
