#ifndef HERO_GRAPHICS_HPP
#define HERO_GRAPHICS_HPP

#include"H_mesh.hpp"
#include"H_math.hpp"
#include"H_shader.hpp"

namespace Hero
{

inline void ClearRenderer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

class Renderer2D
{
private:
    static Renderer2D* instance;

    Mesh mesh;
    matrix4x4 view;
    Shader* currentShader;
public:
    Renderer2D(int width, int height);
    ~Renderer2D();

    static inline Mesh* GetMesh(){ return &instance->mesh; }
    static inline matrix4x4* GetViewMatrix(){ return &instance->view; }
    static inline Shader* GetShader(){ return instance->currentShader; }
    static inline void SetShader(Shader* shader)
    { 
        instance->currentShader = shader; 
        shader->Bind();
    }
};

}
#endif