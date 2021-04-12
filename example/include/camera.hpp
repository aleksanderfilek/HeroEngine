#ifndef CAMERA_HPP
#define CAMERA_HPP

#include"Hero.hpp"

#include"emath.hpp"

#include<cmath>

class Camera: public Hero::GameObject
{
private:
    unsigned int viewLoc, projectionLoc;
    Hero::matrix4x4 viewMatrix;
    Hero::matrix4x4 projectionMatrix;
    
    Hero::float3 worldPosition = {0.0f, 0.0f, 0.0f};
    Hero::float3 localPosition = {0.0f, 0.0f, 0.0f};
    Hero::float3 lookTarget = {0.0f, 0.0f, 1.0f};

    Hero::float3* targetPosition;

public:
    Camera(unsigned int _viewLoc, unsigned int _projectionLoc);

    void Start();
    void Update();
    void Draw();
    void Close();

    inline void SetTarget(Hero::float3* _target){ targetPosition = _target; }
    //Hero::float3 ScreenToWorldVector();

    inline void BindViewMatrix(unsigned int loc){
        glUniformMatrix4fv(loc, 1, GL_FALSE, &this->viewMatrix.v[0].x);}
    inline void BindProjectionMatrix(unsigned int loc){
        glUniformMatrix4fv(loc, 1, GL_FALSE, &this->projectionMatrix.v[0].x);}
};

#endif