#ifndef HERO_WINDOW_HPP
#define HERO_WINDOW_HPP

#include<SDL2/SDL.h>
#include<GL/glew.h>

#include"H_math.hpp"

namespace Hero
{
namespace Window
{
    namespace Engine{
        void Init(const char *title, int width, int height, int sdlflags);
        void Delete();
    }
    
    void Render();

    inline int2 GetScreenSize();
    inline SDL_Window* GetWindow();
    inline SDL_GLContext GetGlContext();
}
}

#endif