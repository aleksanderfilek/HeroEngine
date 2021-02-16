#ifndef H_timer_HPP
#define H_timer_HPP

#include"H_game.hpp"

namespace Hero
{
namespace Time
{
    #ifdef ENGINE
        void Init();
        void Delete();
        void SetDeltaTime(double value);
    #endif

    double GetDeltaTime();
    void SetScale(double value);
    double GetScale();
}
}

#endif