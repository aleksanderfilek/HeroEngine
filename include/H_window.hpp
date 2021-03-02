#ifndef HERO_WINDOW_HPP
#define HERO_WINDOW_HPP

#include<GL\glew.h>
#include<SDL\SDL.h>
#include<SDL\SDL_opengl.h>
#include<SDL\SDL_ttf.h>
#include<GL\glu.h>
#include<GL\gl.h>


#include<iostream>

#include"H_math.hpp"

namespace Hero
{

    class Window
    {
    private:
        int2 screenSize;
        bool fullScreen;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_GLContext glContext;
    public:
        Window(const char *title, int width, int height, int sdlflags);
        ~Window();

        int2 GetScreenSize();
        SDL_Window* GetWindow();
        SDL_Renderer* GetRenderer();
        SDL_GLContext GetGlContext();

        void Render();//tymczasowo
    };

}

#endif