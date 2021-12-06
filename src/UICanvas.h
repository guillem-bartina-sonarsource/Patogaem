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

    UICanvas(const sf::Vector2f& size, UICanvasStyle style, UIComponent* content);
    ~UICanvas();

    //get size of content if fit H or fit V then scale it, otehgrwise check if any axis need slider and
    // add the necesary sliders

    void setParent(UIBox* parent) override;

    //void setSize(const sf::Vector2f& size) override;

    void handleEvents(const sf::Event& event) override;

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

    sf::Vector2f size;
    UICanvasStyle style;
    UIComponent* content;

    UIBox* inner;
    sf::Vector2f offset, maxOffset;
    UIBox* canvas;

};

#endif