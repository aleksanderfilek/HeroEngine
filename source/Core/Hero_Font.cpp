#include"Core/Hero_Font.hpp"

namespace Hero
{

Font* LoadFont(const std::string& path, int size)
{
        Font* font = TTF_OpenFont(path.c_str(), size);

        if(!font)
        {
                std::cout<<"Could not load font! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
                return nullptr;
        }

        return font;
}

void UnloadFont(Font* font)
{
        TTF_CloseFont(font);
}

}