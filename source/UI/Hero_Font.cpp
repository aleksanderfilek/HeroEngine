#include"UI/Hero_Font.hpp"

namespace Hero
{

Font::Font(const std::string& path, int size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if(!font)
    {
        std::cout<<"Could not load font! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
        return;
    }

    this->_font = font;
}

Font::~Font()
{
    TTF_CloseFont(this->_font);
    this->_font = nullptr;
}

}