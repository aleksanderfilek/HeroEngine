#include"camera.hpp"

#define CalculateLocalPosition(n,a)\
    this->localPosition = {0.0f, n, -n};\
    float tz = localPosition.y/tanf(Hero::deg2rad(a));\
    this->lookTarget = {0.0f, -localPosition.y, tz};

Camera::Camera(unsigned int _viewLoc, unsigned int _projectionLoc)
{
    this->viewLoc = _viewLoc;
    this->projectionLoc = _projectionLoc;

    Hero::matrix_projection(this->projectionMatrix, 1280, 720, 60.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(this->projectionLoc, 1, GL_FALSE, &this->projectionMatrix.v[0].x);
    glCheckError();
}


void Camera::Start()
{
    CalculateLocalPosition(10.0f, 45.0f);
}

void Camera::Update()
{
    
    this->worldPosition = Float3Lerp(this->worldPosition, 
                            *this->targetPosition, 2.0f*Hero::Time::GetDeltaTime());

    Hero::float3 calcPos = Hero::add(this->worldPosition, this->localPosition);

    Hero::float3 up = {0.0f, 1.0f, 0.0f};
    Hero::float3 forward = Hero::add(calcPos, this->lookTarget);

    Hero::matrix_lookAt(this->viewMatrix, 
                    calcPos, 
                    forward, 
                    {0.0f, 1.0f, 0.0f});
}

void Camera::Draw()
{
    glUniformMatrix4fv(this->viewLoc, 1, GL_FALSE, &this->viewMatrix.v[0].x);
    glCheckError();
}

void Camera::Close()
{

}

/*
Hero::float3 Camera::ScreenToWorldVector()
{
    Hero::float3 calcPos = Hero::add(this->worldPosition, this->localPosition);

    int xs, ys;
    Hero::Input::getMousePosition(&xs, &ys);

    Hero::float4 screenVec =
    {
        (2.0f*(float)xs/1280) - 1,
        -((2.0f*(float)ys/720) - 1),
        1.0f,
        1.0f
    };

    float* projectionInversed = new float[16];
    float* projectionArr = MatrixToArray(this->projectionMatrix);
    matrix_invert(projectionArr, projectionInversed);
    Hero::matrix4x4 invertedProjection = ArrayToMatrix(projectionInversed);
    Hero::float4 eyeCoord = matrix_vector(invertedProjection, screenVec);
    eyeCoord.z = 1.0f;
    eyeCoord.w = 0.0f;
    delete[] projectionInversed;
    delete[] projectionArr;


    float* viewInvertedArr = new float[16];
    float* viewArr = MatrixToArray(this->viewMatrix);
    matrix_invert(viewArr, viewInvertedArr);
    Hero::matrix4x4 invertedView = ArrayToMatrix(viewInvertedArr); 
    Hero::float4 rayWorld = matrix_vector(invertedView, eyeCoord);
    delete[] viewArr;
    delete[] viewInvertedArr;

    Hero::float3 mouseRay = {rayWorld.x,rayWorld.y,rayWorld.z};
    Hero::normalize(mouseRay);

    return mouseRay;
}
*/