#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include"Hero.hpp"

struct Transform
{
    Hero::float3 position;
    Hero::float3 rotation;
    Hero::float3 scale;
};

#endif