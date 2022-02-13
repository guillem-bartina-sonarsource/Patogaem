#ifndef UISELECTABLEITEMLIST_HPP
#define UISELECTABLEITEMLIST_HPP

#include <functional>
#include <vector>
#include <set>

#include "UIItemList.hpp"
#include "UIRect.h"
#include "UIButton.h"

template<class ItemClass>
class UISelectableItemList : public UIItemList<ItemClass>
{
    public:

    UISelectableItemList(std::set<unsigned int>* bound, bool multiselection, EUIItemListOrientation orientation, float itemLength, std::function<UIComponent*(ItemClass)> itemBuilder, const std::vector<ItemClass>& items);
    ~UISelectableItemList();

    void setSize(const sf::Vector2f& size) override;

    private:

    void clicked(unsigned int index, UIRect* selection);

    using UIItemList<ItemClass>::orientation;
    using UIItemList<ItemClass>::itemLength;
    using UIItemList<ItemClass>::builtItems;
    using UIItemList<ItemClass>::content;

    std::set<unsigned int>* bound;
    const bool multiselection;

};

template<class ItemClass>
UISelectableItemList<ItemClass>::UISelectableItemList(std::set<unsigned int>* bound, bool multiselection, EUIItemListOrientation orientation, float itemLength, std::function<UIComponent*(ItemClass)> itemBuilder, const std::vector<ItemClass>& items)
: UIItemList<ItemClass>(orientation, itemLength, itemBuilder, items),
bound(bound),
multiselection(multiselection)
{}

template<class ItemClass>
UISelectableItemList<ItemClass>::~UISelectableItemList() {}

template<class ItemClass>
void UISelectableItemList<ItemClass>::setSize(const sf::Vector2f& size)
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
    UIRectStyle rectStyle = {
        sf::Color::Transparent,
        0.f,
        sf::Color::Transparent
    };
    
    std::vector<UIComponent*> boxedItems;
    if(orientation == EUIItemListOrientation::EUIItemListOrientation_VERTICAL)
    {
        for(unsigned int i = 0; i < builtItems.size(); i++)
        {
            UIRect* selection = new UIRect(rectStyle, EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(-1.f, -1.f));
            boxedItems.push_back(new UIBox(sf::Vector2f(0.f, i * itemLength), sf::Vector2f(size.x - 10.f, itemLength),
                new UIComponentSet({
                    new UIButton([i, selection, this]{ clicked(i, selection); }, buttonStyle, EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(-1.f, -1.f)),
                    selection,
                    builtItems[i]}, true))
                    );
        }
    }
    else if(orientation == EUIItemListOrientation::EUIItemListOrientation_HORIZONTAL)
    {
        for(unsigned int i = 0; i < builtItems.size(); i++)
        {
            UIRect* selection = new UIRect(rectStyle, EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(-1.f, -1.f));
            boxedItems.push_back(new UIBox(sf::Vector2f(i * itemLength, 0.f), sf::Vector2f(itemLength, size.y - 10.f),
                new UIComponentSet({
                    new UIButton([i, selection, this]{ clicked(i, selection); }, buttonStyle, EUIAlign::EUIAlign_NONE, EUIFit::EUIFit_NONE, sf::Vector2f(), sf::Vector2f(-1.f, -1.f)),
                    selection,
                    builtItems[i]}, true))
                    );
        }
    }

    content = new UIComponentSet(boxedItems);

    UICanvas::setSize(size);
}

template<class ItemClass>
void UISelectableItemList<ItemClass>::clicked(unsigned int index, UIRect* selection)
{
    if(bound->contains(index))
    {
        bound->erase(index);
        selection->setFillColor(sf::Color::Transparent);
    }
    else
    {
        if(multiselection or bound->empty())
        {
            bound->insert(index);
            selection->setFillColor(sf::Color(220, 220, 220, 220));
        }
    }
}

#endif