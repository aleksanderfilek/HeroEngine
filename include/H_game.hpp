#ifndef H_game_HPP
#define H_game_HPP

#include"H_level.hpp"
#include"H_window.hpp"
#include"H_event.hpp"
#include"H_input.hpp"
#include"H_time.hpp"

#include"SDL.h"

#include<cstdio>
#include<stdint.h>

namespace Hero
{

namespace Game
{
    void Init(const char *title, int width, int height, int sdlflags = 0);
    void Start(Level* startLevel);
    void Close();

    void SetLevel(Level* level);
}
}

#endif