#include"Systems/Hero_Window.hpp"

namespace Hero
{

const char* Window::name = "Window System";

Window::Window(const char *title, int width, int height, int sdlflags)
{
    this->_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, sdlflags | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(!this->_window){
        std::cout<<"["<<name<<"] Window could not be created! SDL Error: "<<SDL_GetError()<<std::endl;
        return;
    }
    
    this->_renderer = SDL_CreateRenderer(this->_window, - 1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!this->_renderer)
    {
        std::cout<<"["<<name<<"] Renderer could not be created! SDL Error: "<<SDL_GetError()<<std::endl;
        return;
    }

    this->_windowInfo = { {width, height}, false };

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                        SDL_GL_CONTEXT_PROFILE_CORE);

    this->_glContext = SDL_GL_CreateContext(this->_window);

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;

    glewInit();

    glViewport(0,0,width, height);

    glClearColor(1.0f,1.0f,1.0f,1.0f);

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    if(TTF_Init() < 0)
    {
        std::cout<<"["<<name<<"] SDL_ttf could not be initialize! SDL_ttf Error: "<<TTF_GetError()<<std::endl;
        return;
    }
}

Window::~Window()
{
    TTF_Quit();

    SDL_GL_DeleteContext(this->_glContext);
    SDL_DestroyRenderer(this->_renderer);
    this->_renderer = nullptr;
    SDL_DestroyWindow(this->_window);
    this->_window = nullptr;
}

void Window::Init()
{
    ISystem::Init();
}

void Window::Update()
{

}

void Window::Close()
{
    ISystem::Close();
}

}

void Apply()
{

}
