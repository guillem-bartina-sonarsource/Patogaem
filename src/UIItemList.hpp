#ifndef UIITEMLIST_HPP
#define UIITEMLIST_HPP

#include <functional>
#include <vector>

#include "UICanvas.h"

/*
struct UIItemListStyle
{
    sf::Color fillColor;
    float outlineThickness;
    sf::Color outlineColor;
    sf::Texture* texture = nullptr;
    std::optional<sf::IntRect> textureRect = std::nullopt;

    static UIItemListStyle defaultStyle()
    {
        return {
            .fillColor = sf::Color::Cyan,
            .outlineThickness = 0.f,
            .outlineColor = sf::Color::Black
        };
    }
};
*/

template<class ItemClass>
class UIItemList : public UICanvas
{
    public:

    // Add Style
    UIItemList(const sf::Vector2f& itemSize, std::function<UIComponent*(ItemClass)> itemBuilder, const std::vector<ItemClass>& items);
    ~UIItemList();

    private:

    static UIComponent* buildItems(const sf::Vector2f& itemSize, std::function<UIComponent*(ItemClass)> itemBuilder, const std::vector<ItemClass>& items);

};

template<class ItemClass>
UIItemList<ItemClass>::UIItemList(const sf::Vector2f& itemSize, std::function<UIComponent*(ItemClass)> itemBuilder, const std::vector<ItemClass>& items)
: UICanvas(sf::Vector2f(itemSize.x, itemSize.y * items.size()), UICanvasStyle{EUICanvasVerticalSliderPosition::RIGHT, EUICanvasHorizontalSliderPosition::EUICanvasHorizontalSliderPosition_NONE, 10.f, itemSize.y}, buildItems(itemSize, itemBuilder, items))
{}

template<class ItemClass>
UIItemList<ItemClass>::~UIItemList() {}

template<class ItemClass>
UIComponent* UIItemList<ItemClass>::buildItems(const sf::Vector2f& itemSize, std::function<UIComponent*(ItemClass)> itemBuilder, const std::vector<ItemClass>& items)
{
    std::vector<UIComponent*> builtItems;

    for(unsigned int i = 0; i < items.size(); i++)
    {
        builtItems.push_back(new UIBox(sf::Vector2f(0.f, itemSize.y * i), itemSize, itemBuilder(items[i])));
    }

    return new UIComponentSet(builtItems);
}

#endif