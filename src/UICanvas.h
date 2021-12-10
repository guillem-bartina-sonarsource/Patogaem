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
    int scrollSensitivity;

    static UICanvasStyle defaultStyle()
    {
        return {
            .verticalSliderPosition = EUICanvasVerticalSliderPosition::RIGHT,
            .horizontalSliderPosition = EUICanvasHorizontalSliderPosition::BOTTOM,
            .sliderThickness = 10.f,
            .scrollSensitivity = 10
        };
    }
};


class UICanvas : public UIComponent
{
    public:

    //Make UICanvar parametrizabe in terms of position and size (UIComponent setParent stuff)
    UICanvas(const sf::Vector2f& canvasSize, UICanvasStyle style, UIComponent* content);
    ~UICanvas();

    void setParent(UIBox* parent) override;

    bool handleEvents(const sf::Event& event) override;

    protected:

    UIComponent* content;

    private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    enum EUICanvasDirection
    {
        DIR_UP = 0,
        DIR_DOWN,
        DIR_LEFT,
        DIR_RIGHT
    };

    void tryMove(EUICanvasDirection direction);

    sf::Vector2f canvasSize;
    UICanvasStyle style;
    
    UIBox* inner;
    bool verticalSlider, horizontalSlider;
    bool showVerticalSlider, showHorizontalSlider;
    sf::Vector2f offset, maxOffset;
    UIBox* canvas;

};

#endif