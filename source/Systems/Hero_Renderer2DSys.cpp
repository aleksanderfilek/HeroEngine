#include"Systems/Hero_Renderer2D.hpp"

namespace Hero
{

const char* Renderer2D::name = "Renderer2D System";

Renderer2D* Renderer2D::instance = nullptr;

Renderer2D::Renderer2D()
{
    Renderer2D::instance = this;
}

Renderer2D::~Renderer2D()
{

}

void Renderer2D::Init()
{
    ISystem::Init();

    this->_windowSystem = Core::GetSystem<Hero::Window>();
    if(!this->_windowSystem)
    {
        this->PrintMessage("Could not find Window System in Core.");
        Core::Close();
    }
}

void Renderer2D::Update()
{
    //handle adding and removig new sprites
}

void Renderer2D::Close()
{
    ISystem::Close();
}

}