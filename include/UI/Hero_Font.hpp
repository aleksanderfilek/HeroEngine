#ifndef HERO_FONT_UI_HPP
#define HERO_FONT_UI_HPP

#include<string>

#include"Hero_Config.hpp"

namespace Hero
{

class Font
{
private:
    TTF_Font* _font = nullptr;
public:
    Font(const std::string& path, int size);
    ~Font();
};

}

#endif