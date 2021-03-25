#ifndef HERO_WINDOW_HPP
#define HERO_WINDOW_HPP

#include"H_defines.hpp"

#include<iostream>

#include"H_math.hpp"

namespace Hero
{

    class WindowSystem
    {
    private:
        int2 screenSize;
        bool fullScreen;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_GLContext glContext;
    public:
        WindowSystem(const char *title, int width, int height, int sdlflags);
        ~WindowSystem();

        int2 GetScreenSize();
        SDL_Window* GetWindow();
        SDL_Renderer* GetRenderer();
        SDL_GLContext GetGlContext();

        void Render();//tymczasowo
    };

}

#endif