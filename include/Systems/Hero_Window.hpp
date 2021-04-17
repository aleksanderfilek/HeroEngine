#ifndef HERO_WINDOW_H
#define HERO_WINDOW_H

#include<iostream>
#include<cstdint>

#include"Hero_Config.hpp"
#include"Hero_Utilities.hpp"
#include"Core/Hero_System.hpp"
#include"Hero_Math.hpp"

namespace Hero
{

struct WindowInfo
{
    int2 screenSize;
    bool fullScreen;
};

class Window : public ISystem
{
private:
    WindowInfo _windowInfo;

    SDL_Window* _window;
    SDL_Renderer* _renderer;
    SDL_GLContext _glContext;
public:
    Window(const char *title, int width, int height, int sdlflags = 0);
    ~Window();

    void Init();
    void Update(double deltaTime);
    void Close();

    static const char* name; 
    const char* GetName(){ return name; }

    std::uint8_t priority(){ return 0; }

    inline SDL_Window* GetWindow(){ return this->_window; }
    inline SDL_Renderer* GetRenderer(){ return this->_renderer; }
    inline SDL_GLContext GetGlContext(){ return this->_glContext; }
    inline WindowInfo* GetWindowInfo(){ return &this->_windowInfo; }
    inline int2 GetScreenSize(){ return this->_windowInfo.screenSize; }

    void Apply(); //aktualizuje okno, rozmiar okna, fullscreen
};

}

#endif