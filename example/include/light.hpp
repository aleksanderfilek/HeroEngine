#ifndef LIGHT_HPP
#define LIGHT_HPP

#include"Hero.hpp"

class Sun
{
private:
    Hero::float3 direction = {0.0f, 0.0f, -1.0f};
    Hero::float3 color = {1.0f, 0.0f, 0.0f};
public:

    void SetDirection(Hero::float3& _direction);

    inline void SetColor(Hero::Color& _color)
            { this->color = {
                (float)_color.r/255.0f, 
                (float)_color.g/255.0f, 
                (float)_color.b/255.0f}; }
    void Bind(unsigned int _sunDirLoc, unsigned int _sunColorLoc);
};

#endif