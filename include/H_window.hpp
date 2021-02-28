#ifndef HERO_WINDOW_HPP
#define HERO_WINDOW_HPP

#include<GL\glew.h>
#include<SDL\SDL.h>
#include<SDL\SDL_opengl.h>
#include<GL\glu.h>
#include<GL\gl.h>


#include<iostream>

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