#ifndef HERO_UIELEMENT_UI_HPP
#define HERO_UIELEMENT_UI_HPP

#include"Core/Hero_Math.hpp"

namespace Hero
{

typedef SDL_Color Color;

class UIElement
{
protected:
    int2 _size = int2zero;
    int2 _relativePosition = int2zero;
    int2 _absolutPosition = int2zero;
public:
    inline int2 GetSize(){ return this->_size; }
    void SetSize(const int2& size){ this->_size = size; }
    inline int2 GetRelativePosition(){ return this->_relativePosition; }
    void SetRelativePosition(const int2& relativePosition);
    inline int2 GetAbsolutePosition(){ return this->_absolutPosition; }
    virtual void SetAbsolutePosition(const int2& absolutePosition);

    virtual void Update() = 0;
    virtual void Draw() = 0;
};

}

#endif