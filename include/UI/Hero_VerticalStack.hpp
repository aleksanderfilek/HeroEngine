#ifndef HERO_VERTICALSTACK_UI_HPP
#define HERO_VERTICALSTACK_UI_HPP

#include"UI/Hero_UIElement.hpp"

namespace Hero
{

class VerticalStack: public UIElement
{
private:

public:
    void Apply();

    void Update(){};
    void Draw();
};

}

#endif