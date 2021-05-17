#ifndef HERO_HORIZONTALSTACK_HPP
#define HERO_HOTIZONTALSTACK_HPP

#include"UI/Hero_UIElement.hpp"

namespace Hero
{

class HorizontalStack: public UIElement
{
private:

public:
    void Apply();

    void Update(){};
    void Draw();
};

}

#endif