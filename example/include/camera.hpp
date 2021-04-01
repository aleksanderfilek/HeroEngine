#ifndef CAMERA_HPP
#define CAMERA_HPP

#include"Hero.hpp"

#include"gameObject.hpp"
#include"components.hpp"

class Camera: public GameObject
{
private:
    Hero::float3 position = {0.0f, 0.0f, 0.0f};
    Hero::float3 target;

    unsigned int viewLoc, projectionLoc;
    Hero::matrix4x4 viewMatrix;
    Hero::matrix4x4 projectionMatrix;
public:
    Camera(unsigned int _viewLoc, unsigned int _projectionLoc);

    void Start();
    void Update();
    void Draw(){}
    void Close();

    inline void SetPosition(Hero::float3& _position){ position = _position; }
    inline Hero::float3 GetPosition(){ return position; }
    inline void SetLookAtTarget(Hero::float3& _target){ target = _target; }

    void SetProjection(int width, int height, float FOV, float near, float far);
};

#endif