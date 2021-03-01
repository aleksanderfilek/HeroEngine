#ifndef HERO_MESH_HPP
#define HERO_MESH_HPP

#include"H_math.hpp"

#include<GL\glew.h>

#include<string>
#include<iostream>
#include<fstream>

namespace Hero
{

    struct Vertex
    {
        float3 position;
        float3 normal;
        float2 uv;
    };

    class Mesh
    {
    private:
        unsigned int _VAO, _VBO, _EBO;

        Vertex* _vertices;
        unsigned int _verticesCount;

        unsigned int* _indices;
        unsigned int _indicesCount;
    public:
        Mesh();
        ~Mesh();

        void SetVertices(Vertex* vertices, unsigned int count);
        void SetIndices(unsigned int* indices, unsigned int count);
        void Load(const std::string& path);
        void Generate();
        void Draw();
    };
}

#endif