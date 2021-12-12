
#include "UITextBox.h"

UITextBox::UITextBox(std::string* bound, UITextBoxStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size)
: UILabel("XXX", style, align, fit, position, size),
bound(bound),
wrtiting(false),
startChar(0)
{
    UIComponent::setSize(sf::Vector2f(size.x, style.characterSize));
}

UITextBox::~UITextBox() {}

void UITextBox::setSize(const sf::Vector2f& size)
{
    UIComponent::setSize(sf::Vector2f(size.x, getSize().y));
}

bool UITextBox::handleEvents(const sf::Event& event)
{
    bool result = false;
    sf::Text* text = static_cast<sf::Text*>(getDrawable());
    switch(event.type)
    {
        case sf::Event::MouseMoved:
        {
            mouseInside = isInside(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
            result = true;
        }
            break;
        case sf::Event::MouseButtonReleased:
        {
            if(mouseInside)
            {
                text->setString(bound->substr(startChar, bound->length()) + "_");
                wrtiting = true;
            }
            result = true;
        }
            break;
        case sf::Event::MouseLeft:
        {
            text->setString(bound->substr(startChar, bound->length()));
            wrtiting = false;
            mouseInside = false;
        }
            break;
        case sf::Event::TextEntered:
        {
            if(wrtiting and event.text.unicode < 128)
            {
                switch (event.text.unicode)
                {
                    case 8:
                    {
                        if(bound->length() > 0)
                        {
                            bound->pop_back();
                            if(startChar > 0)
                            {
                                startChar--;
                            }
                        }
                    }
                        break;
                    default:
                    {
                        bound->push_back(char(event.text.unicode));
                    }
                        break;
                }
            }
            text->setString(bound->substr(startChar, bound->length()) + "_");
            while(text->getLocalBounds().width > getSize().x)
            {
                startChar++;
                text->setString(bound->substr(startChar, bound->length()) + "_");
            }
            if(startChar > 0)
            {
                text->setPosition(sf::Vector2f(getSize().x - text->getLocalBounds().width, 0.f));
            }
            result = true;
        }
            break;
        default:
            break;
    }
    return result;
}
