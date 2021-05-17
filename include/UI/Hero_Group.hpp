#ifndef HERO_GROUP_UI_HPP
#define HERO_GROUP_UI_HPP

#include<vector>

#include"Core/Hero_Math.hpp"
#include"UI/Hero_UIElement.hpp"

namespace Hero
{

class Group: public UIElement
{
private:
    std::vector<UIElement*> elements;
public:
    Group();
    ~Group();

    inline uint32_t GetCount(){ return elements.size(); }
    void SetAbsolutePosition(const int2& absolutePosition);

    void Update();
    void Draw();

    uint32_t Add(UIElement* element);
    void Remove(uint32_t index);
    void Clear();
};

}

#endif