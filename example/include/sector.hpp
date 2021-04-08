#ifndef SECTOR_HPP
#define SECTOR_HPP

#include"Hero.hpp"

#include<cmath>

#define SECTOR_SCALE 10

class Sector: public Hero::Level
{
private:
    void OnStart() override;
    void OnUpdate() override;
    void OnDraw() override;
    void OnClose() override;

    Hero::matrix4x4 modelMatrix;
    Hero::Mesh*& mesh;
    unsigned int modelLoc;

public:
    Sector(Hero::Mesh*& _mesh, unsigned int _modelLoc, Hero::float3 _position);

    void SetPosition(Hero::float3& position);
};

#endif