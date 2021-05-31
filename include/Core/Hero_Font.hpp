#ifndef HERO_FONT_HPP
#define HERO_FONT_HPP

#include<iostream>
#include<string>

#include"Hero_Config.hpp"

namespace Hero
{

typedef TTF_Font Font;
Font* LoadFont(const std::string& path, int size);
void UnloadFont(Font* font);

}

#endif