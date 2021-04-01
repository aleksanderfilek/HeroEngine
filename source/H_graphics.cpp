#include"H_graphics.hpp"

namespace Hero
{
Renderer2D* Renderer2D::instance = nullptr;

Renderer2D::Renderer2D(int width, int height)
{
    this->instance = this;
    this->mesh.Load("example/resources/models/plane.daebin");
    Hero::matrix_orthographic(this->view, width, height, 0, 100);
}

Renderer2D::~Renderer2D()
{

}

}