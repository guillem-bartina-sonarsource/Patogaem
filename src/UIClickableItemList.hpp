#ifndef UICLICKABLEITEMLIST_HPP
#define UICLICKABLEITEMLIST_HPP

#include <functional>
#include <vector>

#include "UIItemList.hpp"
#include "UIButton.h"

template<class ItemClass>
class UIClickableItemList : public UIItemList<ItemClass>
{
    public:

    typedef std::function<void(unsigned int)> UIClickableItemListCallback;

    UIClickableItemList(UIClickableItemListCallback callback, EUIItemListOrientation orientation, float itemLength, std::function<UIComponent*(ItemClass)> itemBuilder, const std::vector<ItemClass>& items);
    ~UIClickableItemList();

    void setSize(const sf::Vector2f& size) override;
    // Avoid code duplication: baseclass sets content, thic class edits contyent of each box?

    private:

    using UIItemList<ItemClass>::orientation;
    using UIItemList<ItemClass>::itemLength;
    using UIItemList<ItemClass>::builtItems;
    using UIItemList<ItemClass>::content;

    const UIClickableItemListCallback callback;

};

template<class ItemClass>
UIClickableItemList<ItemClass>::UIClickableItemList(UIClickableItemListCallback callback, EUIItemListOrientation orientation, float itemLength, std::function<UIComponent*(ItemClass)> itemBuilder, const std::vector<ItemClass>& items)
: UIItemList<ItemClass>(orientation, itemLength, itemBuilder, items),
callback(callback)
{}

template<class ItemClass>
UIClickableItemList<ItemClass>::~UIClickableItemList() {}

template<class ItemClass>
void UIClickableItemList<ItemClass>::setSize(const sf::Vector2f& size)
{
    UIButtonStyle buttonStyle = {
        {
            sf::Color::Transparent,
            0.f,
            sf::Color::Transparent
        },
        sf::Color(160, 160, 160, 160),
        sf::Color(220, 220, 220, 220)
    };

    const UIClickableItemListCallback& callback = this->callback;

    std::vector<UIComponent*> boxedItems;
    if(orientation == EUIItemListOrientation::EUIItemListOrientation_VERTICAL)
    {
        for(unsigned int i = 0; i < builtItems.size(); i++)
        {
            boxedItems.push_back(new UIBox(sf::Vector2f(0.f, i * itemLength), sf::Vector2f(size.x - 10.f, itemLength),
                new UIComponentSet({
                    new UIButton([&callback, i]{ callback(i); }, buttonStyle, EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(-1.f, -1.f)),
                    builtItems[i]}, true))
                    );
        }
    }
    else if(orientation == EUIItemListOrientation::EUIItemListOrientation_HORIZONTAL)
    {
        for(unsigned int i = 0; i < builtItems.size(); i++)
        {
            boxedItems.push_back(new UIBox(sf::Vector2f(i * itemLength, 0.f), sf::Vector2f(itemLength, size.y - 10.f),
                new UIComponentSet({
                    new UIButton([&callback, i]{ callback(i); }, buttonStyle, EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(-1.f, -1.f)),
                    builtItems[i]}, true))
                    );
        }
    }

    content = new UIComponentSet(boxedItems);

    UICanvas::setSize(size);
}

#endif