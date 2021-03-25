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
public:
    Game(const char *title, int width, int height, int sdlflags = 0);
    ~Game();

    void Start(Level* startLevel);

    void SetLevel(Level* level);

    static WindowSystem* GetWindowSystem();
    static EventSystem* GetEventSystem();
    static InputSystem* GetInputSystem();
};

}

#endif