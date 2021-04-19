#ifndef HERO_TEXTURE_HPP
#define HERO_TEXTURE_HPP

#include<iostream>
#include<string>

#include"Core/Hero_Config.hpp"
#include"Core/Hero_Utilities.hpp"
#include"Core/Hero_Math.hpp"

namespace Hero
{

class Texture
{
private:
    unsigned int _glId;
    int2 _size;

public:
    Texture(const std::string& path);
    ~Texture();

    void Bind();
    static void Unbind();

    int2 GetSize(){ return this->_size; }
    unsigned int GetGlID(){ return this->_glId; }
};

}

#endif