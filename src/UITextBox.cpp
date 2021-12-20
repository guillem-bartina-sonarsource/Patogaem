
#include "UITextBox.h"

#include <iostream>

UITextBox::UITextBox(std::string* bound, UITextBoxStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size)
: UIRect(style, align, fit, position, sf::Vector2f(size.x, style.font.getLineSpacing(style.characterSize) * 1.1f)),
bound(bound),
charLength(style.font.getGlyph(int('#'), style.characterSize, style.style & sf::Text::Bold, style.outlineThickness).advance),
wrtiting(false),
startChar(0),
endChar(1),
showCursor(false),
cursorTimer(sf::Time::Zero),
cursorPosition(0)
{
    *bound = "";
    text.setPosition(5.f, 0.f);
    text.setFont(style.font);
    text.setCharacterSize(style.characterSize);
    text.setStyle(style.style);
    text.setFillColor(style.fillColor);
    text.setOutlineThickness(style.outlineThickness);
    text.setOutlineColor(style.outlineColor);
    text.setString(" ");
}

UITextBox::~UITextBox() {}

void UITextBox::setSize(const sf::Vector2f& size)
{
    UIRect::setSize(sf::Vector2f(size.x, getSize().y));
}

bool UITextBox::handleEvents(const sf::Event& event)
{
    bool result = false;
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
                wrtiting = true;
                showCursorNow();
            }
            result = true;
        }
            break;
        case sf::Event::MouseLeft:
        {
            std::string boundCopy = (*bound + ' ').substr(startChar, endChar-startChar);
            text.setString(boundCopy);
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
                            if(cursorPosition == bound->length())
                            {
                                bound->pop_back();
                                endChar--;
                            }
                            else
                            {
                                for(unsigned int i = cursorPosition; i < bound->length(); i++)
                                {
                                    bound->at(i) = bound->at(i+1);
                                }
                                bound->pop_back();
                            }

                            while(startChar > 0 and (endChar-startChar+1) * charLength <= getSize().x - (5.f * 2))
                            {
                                startChar--;
                            }

                            if(startChar == 0)
                            {
                                text.setPosition(sf::Vector2f(5.f, 0.f));
                            }

                            cursorPosition--;
                            showCursorNow();
                        }
                    }
                        break;
                    default:
                    {
                        if(cursorPosition == bound->length())
                        {
                            bound->push_back(char(event.text.unicode));
                            endChar++;

                            while((endChar-startChar) * charLength > getSize().x - (5.f * 2))
                            {
                                startChar++;
                            }
                            
                            if(startChar > 0)
                            {
                                text.setPosition(sf::Vector2f(getSize().x - (endChar-startChar)*charLength - 5.f, 0.f));
                            }
                        }
                        else
                        {
                            bound->at(cursorPosition) = char(event.text.unicode);
                        }
                        cursorPosition++;
                        showCursorNow();
                    }
                        break;
                }
            }
            result = true;
        }
            break;
        case sf::Event::KeyPressed:
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Left:
                {
                    if(cursorPosition > 0)
                    {
                        cursorPosition--;
                        if(cursorPosition < startChar)
                        {
                            startChar--;
                            endChar--;
                        }
                    }
                    showCursorNow();
                }
                    break;
                case sf::Keyboard::Right:
                {
                    if(cursorPosition < bound->length())
                    {
                        cursorPosition++;
                        if(cursorPosition >= endChar)
                        {
                            startChar++;
                            endChar++;
                        }
                    }
                    showCursorNow();
                }
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
    return result;
}

void UITextBox::update(const sf::Time deltatime)
{
    if(wrtiting)
    {
        cursorTimer += deltatime;
        if(cursorTimer > sf::seconds(0.8f))
        {
            cursorTimer -= sf::seconds(0.8f);
            showCursor = !showCursor;
            std::string boundCopy = (*bound + ' ').substr(startChar, endChar-startChar);
            if(showCursor)
            {
                boundCopy[cursorPosition-startChar] = '_';
            }
            text.setString(boundCopy);
        }
    }
}

void UITextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    UIComponent::draw(target, states);

    sf::RenderStates renderStatesCopy(states);
    renderStatesCopy.transform *= getTransform();
    target.draw(text, renderStatesCopy);
}

void UITextBox::showCursorNow()
{
    showCursor = true;
    cursorTimer = sf::Time::Zero;

    std::string boundCopy = (*bound + ' ').substr(startChar, endChar-startChar);
    boundCopy[cursorPosition-startChar] = '_';
    text.setString(boundCopy);
}