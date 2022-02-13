#ifndef UIITEMLIST_HPP
#define UIITEMLIST_HPP

#include <functional>
#include <vector>

#include "UIComponentSet.h"
#include "UICanvas.h"

enum EUIItemListOrientation
{
    EUIItemListOrientation_VERTICAL,
    EUIItemListOrientation_HORIZONTAL
};

template<class ItemClass>
class UIItemList : public UICanvas
{
    public:

    // Add Style
    UIItemList(EUIItemListOrientation orientation, float itemLength, std::function<UIComponent*(ItemClass)> itemBuilder, const std::vector<ItemClass>& items);
    ~UIItemList();

    virtual void setSize(const sf::Vector2f& size) override;

    protected:

    const EUIItemListOrientation orientation;
    const float itemLength;
    std::vector<UIComponent*> builtItems;
};

template<class ItemClass>
UIItemList<ItemClass>::UIItemList(EUIItemListOrientation orientation, float itemLength, std::function<UIComponent*(ItemClass)> itemBuilder, const std::vector<ItemClass>& items)
: UICanvas(sf::Vector2f(orientation == EUIItemListOrientation::EUIItemListOrientation_HORIZONTAL ? items.size() * itemLength : -1.f, orientation == EUIItemListOrientation::EUIItemListOrientation_VERTICAL ? items.size() * itemLength : -1.f), UICanvasStyle{EUICanvasVerticalSliderPosition::RIGHT, EUICanvasHorizontalSliderPosition::BOTTOM, 10.f, itemLength}, nullptr),
orientation(orientation),
itemLength(itemLength)
{
    for(unsigned int i = 0; i < items.size(); i++)
    {
        builtItems.push_back(itemBuilder(items[i]));
    }
}

template<class ItemClass>
UIItemList<ItemClass>::~UIItemList() {}

template<class ItemClass>
void UIItemList<ItemClass>::setSize(const sf::Vector2f& size)
{
    std::vector<UIComponent*> boxedItems;
    if(orientation == EUIItemListOrientation::EUIItemListOrientation_VERTICAL)
    {
        for(unsigned int i = 0; i < builtItems.size(); i++)
        {
            boxedItems.push_back(new UIBox(sf::Vector2f(0.f, i * itemLength), sf::Vector2f(size.x - 10.f, itemLength), builtItems[i]));
        }
    }
    else if(orientation == EUIItemListOrientation::EUIItemListOrientation_HORIZONTAL)
    {
        for(unsigned int i = 0; i < builtItems.size(); i++)
        {
            boxedItems.push_back(new UIBox(sf::Vector2f(i * itemLength, 0.f), sf::Vector2f(itemLength, size.y - 10.f), builtItems[i]));
        }
    }

    content = new UIComponentSet(boxedItems);

    UICanvas::setSize(size);
}

#endif