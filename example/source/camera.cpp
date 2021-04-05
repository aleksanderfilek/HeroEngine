#include"camera.hpp"

inline Hero::float3 Float3Lerp(const Hero::float3& p0, const Hero::float3& p1, float t);

Camera::Camera(unsigned int _viewLoc, unsigned int _projectionLoc)
{
    this->viewLoc = _viewLoc;
    this->projectionLoc = _projectionLoc;
}

void Camera::Start()
{
    this->localPosition = {0.0f, 10.0f, -10.0f};
    float tz = localPosition.y/tanf(Hero::deg2rad(45.0f));
    this->lookTarget = {0.0f, -localPosition.y, tz};
}

void Camera::Update()
{

    this->worldPosition = Float3Lerp(this->worldPosition, 
                            *this->targetPosition, Hero::Time::GetDeltaTime());

    Hero::float3 calcPos = Hero::add(this->worldPosition, this->localPosition);

    Hero::float3 up = {0.0f, 1.0f, 0.0f};
    Hero::float3 forward = Hero::add(calcPos, this->lookTarget);
    Hero::matrix_lookAt(viewMatrix, calcPos, forward, up);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &this->viewMatrix.v[0].x);  

    ScreenToWorldVector();
}

void Camera::Close()
{

}

Hero::int2 Camera::GetSectorIndices() const
{
    Hero::float3 calcPos = Hero::add(this->worldPosition, this->localPosition);

    Hero::int2 value = {
        (int)floor(calcPos.x)/SECTOR_SCALE, 
        0
    };

    float t = this->lookTarget.z/this->lookTarget.y;
    t *= -calcPos.y;
    t += calcPos.z;

    value.y = floor(t)/SECTOR_SCALE;

    return value;
}

void Camera::SetProjection(int width, int height, float FOV, float near, float far)
{
    Hero::matrix_projection(this->projectionMatrix, width, height, FOV, near, far);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &this->projectionMatrix.v[0].x);
}

Hero::float3 Float3Lerp(const Hero::float3& p0, const Hero::float3& p1, float t)
{
    float x = (1 - t)*p0.x + t*p1.x;
    float y = (1 - t)*p0.y + t*p1.y;
    float z = (1 - t)*p0.z + t*p1.z;
    return {x, y, z};
}

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
    delete projectionInversed;
    delete projectionArr;


    float* viewInvertedArr = new float[16];
    float* viewArr = MatrixToArray(this->viewMatrix);
    matrix_invert(viewArr, viewInvertedArr);
    Hero::matrix4x4 invertedView = ArrayToMatrix(viewInvertedArr); 
    Hero::float4 rayWorld = matrix_vector(invertedView, eyeCoord);
    delete viewArr;
    delete viewInvertedArr;

    Hero::float3 mouseRay = {rayWorld.x,rayWorld.y,rayWorld.z};
    Hero::normalize(mouseRay);

    //std::cout<<mouseRay.x<<" "<<mouseRay.y<<" "<<mouseRay.z<<std::endl;


    float x = calcPos.x - (mouseRay.x/mouseRay.y)*calcPos.y;
    float y = 0.0f;
    float z = calcPos.z - (mouseRay.z/mouseRay.y)*calcPos.y;

    std::cout<<x<<" "<<y<<" "<<z<<std::endl;

    return {x,y,z};
}