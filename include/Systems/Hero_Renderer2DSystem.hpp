#ifndef HERO_RENDERER2D_HPP
#define HERO_RENDERER2D_HPP

#include<cstdint>

#include"Hero_Config.hpp"
#include"Core/Hero_Core.hpp"
#include"Core/Hero_System.hpp"
#include"Systems/Hero_WindowSystem.hpp"

namespace Hero
{

class Renderer2D : public ISystem
{
private:
    static Renderer2D* instance;

    Window* _windowSystem;

public:
    Renderer2D();
    ~Renderer2D();

    void Init();
    void Update();
    void Close();

    static const char* name; 
    const char* GetName(){ return name; }

    static inline void ClearColor(float red, float green, float blue)
        { glClearColor(red, green, blue, 1.0f); }
    static inline void ClearColor(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
        { glClearColor((float)red/255.0f, (float)green/255.0f, (float)blue/255.0f, 1.0f); }

    static inline void Clear()
        { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    static inline void Render(){ Renderer2D::instance->_windowSystem->Render(); }
};

}
#endif