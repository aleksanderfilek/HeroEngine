#include"camera.hpp"

Camera::Camera(unsigned int _viewLoc, unsigned int _projectionLoc)
{
    this->viewLoc = _viewLoc;
    this->projectionLoc = _projectionLoc;
}

void Camera::Start()
{

}

void Camera::Update()
{
    Hero::float3 up = {0.0f, 1.0f, 0.0f};
    Hero::float3 forward = Hero::add(this->position, this->target);
    Hero::matrix_lookAt(viewMatrix, this->position, forward, up);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &this->viewMatrix.v[0].x);  
}

void Camera::Close()
{

}

void Camera::SetProjection(int width, int height, float FOV, float near, float far)
{
    Hero::matrix_projection(this->projectionMatrix, width, height, FOV, near, far);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &this->projectionMatrix.v[0].x);
}