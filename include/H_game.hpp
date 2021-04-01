#ifndef H_game_HPP
#define H_game_HPP

#include"H_level.hpp"
#include"H_window.hpp"
#include"H_event.hpp"
#include"H_input.hpp"
#include"H_time.hpp"
#include"H_graphics.hpp"

#include"H_defines.hpp"

#include<cstdio>
#include<stdint.h>

namespace Hero
{

class Game
{
private:
    static Game* instance;

    WindowSystem* windowSystem;
    EventSystem* eventSystem;
    InputSystem* inputSystem;
    Renderer2D* renderer;

    Time* globalTime;

    Level* currentLevel = nullptr;
    Level* nextLevel = nullptr;

    void CheckLevel();
    void CloseLevel();

    #if RUNTIME_INJECTION == 1
        Event* runtimeInjection;
    #endif
public:
    Game(const char *title, int width, int height, int sdlflags = 0);
    ~Game();

    void Start(Level* startLevel);

    static void SetLevel(Level* level);

    static WindowSystem* GetWindowSystem();
    static EventSystem* GetEventSystem();
    static InputSystem* GetInputSystem();

    #if RUNTIME_INJECTION == 1
        inline static void RuntimeInject(EventFunction function){ 
            instance->runtimeInjection->Add(function); }
        inline static void RuntimeInjectionClear(){
            instance->runtimeInjection->Clear(); }
    #endif
};

}

#endif