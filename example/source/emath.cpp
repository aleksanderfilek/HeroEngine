#include"emath.hpp"

Hero::float4 matrix_vector(Hero::matrix4x4& matrix, Hero::float4& vector)
{
    float x = vector.x*matrix.v[0].x + vector.y*matrix.v[1].x + vector.z*matrix.v[2].x + vector.w*matrix.v[3].x;
    float y = vector.x*matrix.v[0].y + vector.y*matrix.v[1].y + vector.z*matrix.v[2].y + vector.w*matrix.v[3].y;
    float z = vector.x*matrix.v[0].z + vector.y*matrix.v[1].z + vector.z*matrix.v[2].z + vector.w*matrix.v[3].z;
    float w = vector.x*matrix.v[0].w + vector.y*matrix.v[1].w + vector.z*matrix.v[2].w + vector.w*matrix.v[3].w;

    return {x, y, z, w};
}

Hero::matrix4x4 matrix_matrix(Hero::matrix4x4& A, Hero::matrix4x4& B)
{
    Hero::matrix4x4 value;

    for(int i = 0; i < 4; i++)
    {
        value.v[i] = matrix_vector(A, B.v[i]);
    }

    return value;
}

Hero::matrix4x4 ArrayToMatrix(const float* array)
{
    Hero::matrix4x4 result;

    result.v[0] = {array[0], array[4], array[8], array[12]};
    result.v[1] = {array[1], array[5], array[9], array[13]};
    result.v[2] = {array[2], array[6], array[10], array[14]};
    result.v[3] = {array[3], array[7], array[11], array[15]};

    return result;
}

float* MatrixToArray(Hero::matrix4x4& matrix)
{
    float* arr = new float[16];

    arr[0] = matrix.v[0].x;
    arr[1] = matrix.v[0].y;
    arr[2] = matrix.v[0].z;
    arr[3] = matrix.v[0].w;

    arr[4] = matrix.v[1].x;
    arr[5] = matrix.v[1].y;
    arr[6] = matrix.v[1].z;
    arr[7] = matrix.v[1].w;

    arr[8] = matrix.v[2].x;
    arr[9] = matrix.v[2].y;
    arr[10] = matrix.v[2].z;
    arr[11] = matrix.v[2].w;

    arr[12] = matrix.v[3].x;
    arr[13] = matrix.v[3].y;
    arr[14] = matrix.v[3].z;
    arr[15] = matrix.v[3].w;

    return arr;
}


bool matrix_invert(const float* m, float*& invOut)
{
    double inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}

float lerp(float a, float b, float t)
{
    return (1 - t)*a + t*b;
}

Hero::float3 Float3Lerp(const Hero::float3& p0, const Hero::float3& p1, float t)
{
    float x = (1 - t)*p0.x + t*p1.x;
    float y = (1 - t)*p0.y + t*p1.y;
    float z = (1 - t)*p0.z + t*p1.z;
    return {x, y, z};
}