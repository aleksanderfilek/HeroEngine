#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include"Hero.hpp"

struct Transform
{
    Hero::float3 position = {0.0f, 0.0f, 0.0f};
    Hero::float3 rotation = {0.0f, 0.0f, 0.0f};
    Hero::float3 scale = {1.0f, 1.0f, 1.0f};
    Hero::matrix4x4 matrix;
};

#endif