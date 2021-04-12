#ifndef UIIMAGE_HPP
#define UIIMAGE_HPP

#include"Hero.hpp"

class Image: public Hero::UIElement
{
private:
    Hero::Texture* texture;
public:
    Image(Hero::Texture* _texture);
    ~Image();
    
    void Update(){};
    void Draw();
};

#endif