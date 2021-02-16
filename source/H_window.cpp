#include"H_window.hpp"

struct WindowData
{
    Hero::int2 screenSize;
    bool fullScreen;
    SDL_Window* window;
    SDL_GLContext glContext;
};

WindowData* windowData;

namespace Hero
{
namespace Window
{
    void Init(const char *title, int width, int height, int sdlflags)
    {
        windowData = new WindowData();

        windowData->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, sdlflags | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        if(!windowData->window){
            printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
            return;
        }

        windowData->screenSize = {width, height};
        windowData->fullScreen = false;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                            SDL_GL_CONTEXT_PROFILE_CORE);

        windowData->glContext = SDL_GL_CreateContext(windowData->window);

        glewExperimental = GL_TRUE;

        glewInit();

        glViewport(0,0,width, height);

        glClearColor(1.0f,1.0f,1.0f,1.0f);
    }

    void Delete()
    {
        SDL_GL_DeleteContext(windowData->glContext);
        
        SDL_DestroyWindow(windowData->window);
        windowData->window = NULL;

        delete windowData;
    }

    void Render()
    {
        SDL_GL_SwapWindow(windowData->window);
    }

    int2 GetScreenSize()
    {
        return windowData->screenSize;
    }

    SDL_Window* GetWindow()
    {
        return windowData->window;
    }

    SDL_GLContext GetGlContext()
    {
        return windowData->glContext;
    }
}
}
