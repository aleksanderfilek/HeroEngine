#include"H_window.hpp"

namespace Hero
{

WindowSystem::WindowSystem(const char *title, int width, int height, int sdlflags)
{
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, sdlflags | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(!this->window){
        std::cout<<"Window could not be created! SDL Error: "<<SDL_GetError()<<std::endl;
        return;
    }
    
    this->renderer = SDL_CreateRenderer(this->window, - 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!this->renderer)
    {
        std::cout<<"Renderer could not be created! SDL Error: "<<SDL_GetError()<<std::endl;
        return;
    }

    this->screenSize = {width, height};
    this->fullScreen = false;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                        SDL_GL_CONTEXT_PROFILE_CORE);

    this->glContext = SDL_GL_CreateContext(this->window);

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;

    glewInit();

    glViewport(0,0,width, height);

    glClearColor(1.0f,1.0f,1.0f,1.0f);

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    if(TTF_Init() < 0)
    {
        std::cout<<"SDL_ttf could not be initialize! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
        return;
    }
}

WindowSystem::~WindowSystem()
{
    TTF_Quit();

    SDL_GL_DeleteContext(this->glContext);
    SDL_DestroyRenderer(this->renderer);
    this->renderer = nullptr;
    SDL_DestroyWindow(this->window);
    this->window = nullptr;
}

int2 WindowSystem::GetScreenSize()
{
    return this->screenSize;
}

SDL_Window* WindowSystem::GetWindow()
{
    return this->window;
}

SDL_Renderer* WindowSystem::GetRenderer()
{
    return this->renderer;
}

SDL_GLContext WindowSystem::GetGlContext()
{
    return this->glContext;
}

void WindowSystem::Render()
{
    SDL_GL_SwapWindow(this->window);
}

}
