#ifndef UICANVAS_HPP
#define UICANVAS_HPP

#include "UIBox.h"
#include "UIComponent.h"


enum EUICanvasVerticalSliderPosition
{
    EUICanvasVerticalSliderPosition_NONE = 0,
    LEFT,
    RIGHT
};

enum EUICanvasHorizontalSliderPosition
{
    EUICanvasHorizontalSliderPosition_NONE = 0,
    TOP,
    BOTTOM
};

struct UICanvasStyle
{
    EUICanvasVerticalSliderPosition verticalSliderPosition;
    EUICanvasHorizontalSliderPosition horizontalSliderPosition;
    float sliderThickness;
    float scrollSensitivity;

    static UICanvasStyle defaultStyle()
    {
        return {
            EUICanvasVerticalSliderPosition::RIGHT,
            EUICanvasHorizontalSliderPosition::BOTTOM,
            10.f,
            10.f
        };
    }
};


class UICanvas : public UIComponent
{
    public:

    //Make UICanvar parametrizabe in terms of position and size (UIComponent setParent stuff)?
    UICanvas(const sf::Vector2f& canvasSize, UICanvasStyle style, UIComponent* content);
    ~UICanvas();

    void setSize(const sf::Vector2f& size) override;

    bool handleEvents(const sf::Event& event) override;

    void update(const sf::Time deltatime) override;

    protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    UIComponent* content;

    private:

    enum EUICanvasDirection
    {
        DIR_UP = 0,
        DIR_DOWN,
        DIR_LEFT,
        DIR_RIGHT
    };

    void tryMove(EUICanvasDirection direction);

    const sf::Vector2f canvasSize;
    const UICanvasStyle style;
    
    UIBox* inner;
    bool verticalSlider, horizontalSlider;
    bool showVerticalSlider, showHorizontalSlider;
    sf::Vector2f offset, maxOffset;
    UIBox* canvas;

};

#endif