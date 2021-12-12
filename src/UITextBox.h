#ifndef UITEXTBOX_HPP
#define UITEXTBOX_HPP

#include "UILabel.h"

struct UITextBoxStyle : UILabelStyle
{
    static UITextBoxStyle defaultStyle(const sf::Font& font)
    {
        return {
            UILabelStyle::defaultStyle(font)
        };
    }
};

class UITextBox : public UILabel
{
    public:

    UITextBox(std::string* bound, UITextBoxStyle style, EUIAlign align, EUIFit fit, const sf::Vector2f& position, const sf::Vector2f& size);
    ~UITextBox();

    void setSize(const sf::Vector2f& size) override;

    bool handleEvents(const sf::Event& event) override;

    private:

    std::string* bound;

    bool mouseInside;
    bool wrtiting;

    unsigned int startChar;
};

#endif