#ifndef CAMERA_HPP
#define CAMERA_HPP

#include"Hero.hpp"

#include"sector.hpp"
#include"emath.hpp"

#include<cmath>

class Camera: public Hero::GameObject
{
private:
    Hero::float3 worldPosition;
    Hero::float3 localPosition = {0.0f, 0.0f, 0.0f};
    Hero::float3 lookTarget = {0.0f, 0.0f, 1.0f};

    Hero::float3* targetPosition;

    unsigned int viewLoc, projectionLoc;
    Hero::matrix4x4 viewMatrix;
    Hero::matrix4x4 projectionMatrix;
    Hero::matrix4x4 projectionViewMatrix;

public:
    Camera(unsigned int _viewLoc, unsigned int _projectionLoc);

    void Start();
    void Update();
    void Draw(){}
    void Close();

    inline void SetTarget(Hero::float3* _target){ targetPosition = _target; }

    Hero::int2 GetSectorIndices() const;
    void SetProjection(int width, int height, float FOV, float near, float far);
    Hero::float3 ScreenToWorldVector();

};

#endif