#ifndef HERO_IMAGE_UI_HPP
#define HERO_IMAGE_UI_HPP

#include"UI/Hero_UIElement.hpp"

namespace Hero
{

class Image: public UIElement
{
private:

public:
    void Apply();

    void Update(){};
    void Draw();
};

}

#endif