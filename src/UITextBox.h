#ifndef UITEXTBOX_HPP
#define UITEXTBOX_HPP

#include "SFML/System/Time.hpp"

#include "UIRect.h"

struct UITextBoxStyle : public UIRectStyle
{
    const sf::Font& font;
    unsigned int characterSize;
    unsigned int style;
    sf::Color fillColor;
    float outlineThickness;
    sf::Color outlineColor;

    static UITextBoxStyle defaultStyle(const sf::Font& font)
    {

        return {
            {
                sf::Color(60, 60, 60),
                -1.f,
                sf::Color(180, 180, 180)
            },
            font,
            30,
            sf::Text::Regular,
            sf::Color::Cyan,
            0.f,
            sf::Color::Black
        };
    }
};

class UITextBox : public UIRect
{
    public:

    UITextBox(std::string* bound, UITextBoxStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size);
    ~UITextBox();

    void setSize(const sf::Vector2f& size) override;

    bool handleEvents(const sf::Event& event) override;

    void update(const sf::Time deltatime) override;

    protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:

    void showCursorNow();

    std::string* bound;

    const float charLength;
    
    bool mouseInside;
    bool wrtiting;

    sf::Text text;
    unsigned int startChar, endChar;
    bool showCursor;
    sf::Time cursorTimer;
    unsigned int cursorPosition;
};

#endif