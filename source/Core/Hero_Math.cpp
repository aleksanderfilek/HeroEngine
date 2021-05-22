#include"Core/Hero_Math.hpp"

namespace Hero
{

float deg2rad(float degree)
{
    return (degree * PI)/180.0f;
}

float rad2deg(float radians)
{
    return (180.0f * radians)/PI;
}

int2 AddI2(const int2& A,const int2& B)
{
    return {A.x + B.x, A.y + B.y};
}

int2 SubstractI2(const int2& A,const int2& B)
{
    return {A.x - B.x, A.y - B.y};
}

int DotProductI2(const int2& A,const int2& B)
{
    return (A.x * B.x) + (A.y * B.y);
}

float DistanceI2(const int2& A, const int2& B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    return sqrtf(x2 + y2);
}

int3 AddI3(const int3& A, const int3& B)
{
    return {A.x + B.x, A.y + B.y, A.z + B.z};
}

int3 Substract(const int3& A, const int3& B)
{
    return {A.x - B.x, A.y - B.y, A.z - B.z};
}

int DotProductI3(const int3& A, const int3& B)
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

float DistanceI3(const int3& A, const int3& B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    float z2 = (A.z - B.z)*(A.z - B.z); 
    return sqrtf(x2 + y2 + z2);
}

int4 AddI4(const int4& A, const int4& B)
{
    return {A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w};
}

int4 SubstractI4(const int4& A, const int4& B)
{
    return {A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w};
}

float LerpF(float a, float b, float t)
{
    return (1 - t)*a + t*b;
}

float2 AddF2(const float2& A,const float2& B)
{
    return {A.x + B.x, A.y + B.y};
}

float2 SubstractF2(const float2& A,const float2& B)
{
    return {A.x - B.x, A.y - B.y};
}

float DotProductF2(const float2& A,const float2& B)
{
    return (A.x * B.x) + (A.y * B.y);
}

float2 MultiplyF2(const float2& A, float k)
{
    return {A.x * k, A.y * k};
}

float2 NormalizeF2(const float2& A)
{
    float length = LengthF2(A);
    float x = A.x / length;
    float y = A.y / length;
    return {x, y};
}

float LengthF2(const float2& A)
{
    return sqrtf(A.x*A.x + A.y*A.y);
}

float DistanceF2(const float2& A, const float2& B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    return sqrtf(x2 + y2);
}

float3 AddF3(const float3& A, const float3& B)
{
    return {A.x + B.x, A.y + B.y, A.z + B.z};
}

float3 SubstractF3(const float3& A, const float3& B)
{
    return {A.x - B.x, A.y - B.y, A.z - B.z};
}

float DotProductF3(const float3& A, const float3& B)
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

float3 CrossProduct(const float3& A, const float3& B)
{
    return {A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.y, A.x*B.y - A.y*B.x};
}

float3 MultiplyF3(const float3& A, float k)
{
    return {A.x * k, A.y * k, A.z * k};
}

float3 NormalizeF3(const float3& A)
{
    float length = LengthF3(A);
    float x = A.x / length;
    float y = A.y / length;
    float z = A.z / length;
    return {x, y, z};
}

float LengthF3(const float3& A)
{
    return sqrtf(A.x*A.x + A.y*A.y + A.z*A.z);
}

float3 LerpF3(const float3& A, const float3& B, float t)
{
    float x = (1 - t)*A.x + t*B.x;
    float y = (1 - t)*A.y + t*B.y;
    float z = (1 - t)*A.z + t*B.z;
    return {x, y, z};
}

float DistanceF3(const float3& A, const float3& B)
{
    float x2 = (A.x - B.x)*(A.x - B.x);
    float y2 = (A.y - B.y)*(A.y - B.y); 
    float z2 = (A.z - B.z)*(A.z - B.z); 
    return sqrtf(x2 + y2 + z2);
}

float4 AddF4(const float4& A, const float4& B)
{
    return {A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w};
}

float4 SubstractF4(const float4& A, const float4& B)
{
    return {A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w};
}

float4 MultiplyF4(const float4& A, float k)
{
    return {A.x * k, A.y * k, A.z * k, A.w * k};
}

float4 NormalizeF4(const float4& A)
{
    float length = LengthF4(A);
    float x = A.x / length;
    float y = A.y / length;
    float z = A.z / length;
    float w = A.w / length;
    return {x, y, z, w};
}

float LengthF4(const float4& A)
{
    return sqrtf(A.x*A.x + A.y*A.y + A.z*A.z + A.w*A.w);
}

matrix2x2 MultiplyM2x2(const matrix2x2& A, const matrix2x2& B)
{
    float x = A.col[0].x * B.col[0].x + A.col[1].x * B.col[0].y;
    float y = A.col[0].y * B.col[0].x + A.col[1].y * B.col[0].y;
    float z = A.col[0].x * B.col[1].x + A.col[1].x * B.col[1].y;
    float w = A.col[0].y * B.col[1].x + A.col[1].y * B.col[1].y;
    matrix2x2 mat = {{{x,y},{z,w}}};  
    return mat;
}   

float DeterminentM2x2(const matrix2x2& A)
{
    return (A.col[0].x * A.col[1].y) - (A.col[0].y * A.col[1].x);
}

matrix2x2 TansponeM2x2(const matrix2x2& A)
{
    return {{{A.col[0].x, A.col[1].x},{A.col[0].y, A.col[1].y}}};
}

matrix2x2 InvertM2x2(const matrix2x2& A)
{
    float det = 1.0f / DeterminentM2x2(A);
    return {{{det * A.col[1].y, det * (-A.col[0].y)},
            {det * (-A.col[1].x), det * A.col[0].x}}};
}

float2 MultiplyM2x2F2(const matrix2x2& matrix, const float2& vector)
{
    float x = matrix.col[0].x * vector.x + matrix.col[1].x * vector.y;
    float y = matrix.col[0].y * vector.x + matrix.col[1].y * vector.y;
    return {x, y};
}

matrix3x3 MultiplyM3x3(const matrix3x3& A, const matrix3x3& B)
{
    matrix3x3 matrix;

    matrix.col[0].x = A.col[0].x * B.col[0].x + A.col[1].x * B.col[0].y + A.col[2].x * B.col[0].z;
    matrix.col[0].y = A.col[0].y * B.col[0].x + A.col[1].y * B.col[0].y + A.col[2].y * B.col[0].z;
    matrix.col[0].z = A.col[0].z * B.col[0].x + A.col[1].z * B.col[0].y + A.col[2].z * B.col[0].z;

    matrix.col[1].x = A.col[0].x * B.col[1].x + A.col[1].x * B.col[1].y + A.col[2].x * B.col[1].z;
    matrix.col[1].y = A.col[0].y * B.col[1].x + A.col[1].y * B.col[1].y + A.col[2].y * B.col[1].z;
    matrix.col[1].z = A.col[0].z * B.col[1].x + A.col[1].z * B.col[1].y + A.col[2].z * B.col[1].z;

    matrix.col[2].x = A.col[0].x * B.col[2].x + A.col[1].x * B.col[2].y + A.col[2].x * B.col[2].z;
    matrix.col[2].y = A.col[0].y * B.col[2].x + A.col[1].y * B.col[2].y + A.col[2].y * B.col[2].z;
    matrix.col[2].z = A.col[0].z * B.col[2].x + A.col[1].z * B.col[2].y + A.col[2].z * B.col[2].z;

    return matrix;
}

float DeterminentM3x3(const matrix3x3& A)
{
    return A.col[0].x*A.col[1].y*A.col[2].z + 
            A.col[1].x*A.col[2].y*A.col[0].z + 
            A.col[2].x*A.col[0].y*A.col[1].z -
            A.col[2].x*A.col[1].y*A.col[0].z - 
            A.col[1].x*A.col[0].y*A.col[2].z - 
            A.col[0].x*A.col[2].y*A.col[1].z;
}

matrix3x3 TansponeM3x3(const matrix3x3& A)
{
    matrix3x3 matrix;

    matrix.col[0].x = A.col[0].x;
    matrix.col[1].x = A.col[0].y;
    matrix.col[2].x = A.col[0].z;
    matrix.col[0].y = A.col[1].x;
    matrix.col[1].y = A.col[1].y;
    matrix.col[2].y = A.col[1].z;
    matrix.col[0].z = A.col[2].x;
    matrix.col[1].z = A.col[2].y;
    matrix.col[2].z = A.col[2].z;

    return matrix;
}

matrix3x3 InvertM3x3(const matrix3x3& A)
{
    float det = 1.0f / DeterminentM3x3(A);

    matrix3x3 matrix;

    matrix.col[0].x = (A.col[1].y * A.col[2].z) - (A.col[2].y * A.col[1].z);
    matrix.col[0].x *= det;
    matrix.col[0].y = (A.col[0].y * A.col[2].z) - (A.col[2].y * A.col[0].z);
    matrix.col[0].y *= -det;
    matrix.col[0].z = (A.col[0].y * A.col[1].z) - (A.col[1].y * A.col[0].z);
    matrix.col[0].z *= det;

    matrix.col[1].x = (A.col[1].x * A.col[2].z) - (A.col[2].x * A.col[1].z);
    matrix.col[1].x *= -det;
    matrix.col[1].y = (A.col[0].x * A.col[2].z) - (A.col[2].x * A.col[0].z);
    matrix.col[1].y *= det;
    matrix.col[1].z = (A.col[0].x * A.col[1].z) - (A.col[1].x * A.col[0].z);
    matrix.col[1].z *= -det;

    matrix.col[2].x = (A.col[1].x * A.col[2].y) - (A.col[2].x * A.col[1].y);
    matrix.col[2].x *= det;
    matrix.col[2].y = (A.col[0].x * A.col[2].y) - (A.col[2].x * A.col[0].y);
    matrix.col[2].y *= -det;
    matrix.col[2].z = (A.col[0].x * A.col[1].y) - (A.col[1].x * A.col[0].y);
    matrix.col[2].z *= det;

    return matrix;
}

float3 MultiplyM3x3F3(const matrix3x3& matrix, const float3& vector)
{
    float3 vec;

    vec.x = matrix.col[0].x * vector.x + matrix.col[1].x * vector.y + matrix.col[2].x * vector.z;
    vec.y = matrix.col[0].y * vector.x + matrix.col[1].y * vector.y + matrix.col[2].y * vector.z;
    vec.z = matrix.col[0].z * vector.x + matrix.col[2].z * vector.y + matrix.col[2].z * vector.z;
    
    return vec;
}

matrix4x4 MultiplyM4x4(const matrix4x4& A, const matrix4x4& B)
{
    matrix4x4 matrix;

    matrix.col[0].x = A.col[0].x * B.col[0].x + A.col[1].x * B.col[0].y + A.col[2].x * B.col[0].z + A.col[3].x * B.col[0].w;
    matrix.col[0].y = A.col[0].y * B.col[0].x + A.col[1].y * B.col[0].y + A.col[2].y * B.col[0].z + A.col[3].x * B.col[0].w;
    matrix.col[0].z = A.col[0].z * B.col[0].x + A.col[1].z * B.col[0].y + A.col[2].z * B.col[0].z + A.col[3].x * B.col[0].w;
    matrix.col[0].w = A.col[0].w * B.col[0].x + A.col[1].w * B.col[0].y + A.col[2].w * B.col[0].z + A.col[3].x * B.col[0].w;

    matrix.col[1].x = A.col[0].x * B.col[1].x + A.col[1].x * B.col[1].y + A.col[2].x * B.col[1].z + A.col[3].x * B.col[1].w;
    matrix.col[1].y = A.col[0].y * B.col[1].x + A.col[1].y * B.col[1].y + A.col[2].y * B.col[1].z + A.col[3].x * B.col[1].w;
    matrix.col[1].z = A.col[0].z * B.col[1].x + A.col[1].z * B.col[1].y + A.col[2].z * B.col[1].z + A.col[3].x * B.col[1].w;
    matrix.col[1].z = A.col[0].w * B.col[1].x + A.col[1].w * B.col[1].y + A.col[2].w * B.col[1].z + A.col[3].x * B.col[1].w;

    matrix.col[2].x = A.col[0].x * B.col[2].x + A.col[1].x * B.col[2].y + A.col[2].x * B.col[2].z + A.col[3].x * B.col[2].w;
    matrix.col[2].y = A.col[0].y * B.col[2].x + A.col[1].y * B.col[2].y + A.col[2].y * B.col[2].z + A.col[3].x * B.col[2].w;
    matrix.col[2].z = A.col[0].z * B.col[2].x + A.col[1].z * B.col[2].y + A.col[2].z * B.col[2].z + A.col[3].x * B.col[2].w;
    matrix.col[2].w = A.col[0].w * B.col[2].w + A.col[1].w * B.col[2].y + A.col[2].w * B.col[2].z + A.col[3].x * B.col[2].w;

    matrix.col[3].x = A.col[0].x * B.col[2].x + A.col[1].x * B.col[2].y + A.col[2].x * B.col[2].z + A.col[3].x * B.col[3].w;
    matrix.col[3].y = A.col[0].y * B.col[2].x + A.col[1].y * B.col[2].y + A.col[2].y * B.col[2].z + A.col[3].x * B.col[3].w;
    matrix.col[3].z = A.col[0].z * B.col[2].x + A.col[1].z * B.col[2].y + A.col[2].z * B.col[2].z + A.col[3].x * B.col[3].w;
    matrix.col[3].w = A.col[0].w * B.col[2].x + A.col[1].w * B.col[2].y + A.col[2].w * B.col[2].z + A.col[3].x * B.col[3].w;

    return matrix;
}

float DeterminentM4x4(const matrix4x4& A)
{    
    matrix4x4 matrix = matrix4x4identity;

    float mul = A.col[0].y / A.col[0].x;
    matrix.col[1].y = A.col[1].y - mul * A.col[1].x;
    matrix.col[2].y = A.col[2].y - mul * A.col[2].x;
    matrix.col[3].y = A.col[3].y - mul * A.col[3].x;

    mul = A.col[0].z / A.col[0].y;
    matrix.col[2].z = A.col[2].z - mul * A.col[2].y;
    matrix.col[3].z = A.col[3].z - mul * A.col[3].y;

    mul = A.col[0].w / A.col[0].z;
    matrix.col[2].w = A.col[2].w - mul * A.col[2].z;

    float det = matrix.col[0].x * matrix.col[1].y * matrix.col[2].z *matrix.col[3].w;

    return 0.0f;
}

matrix4x4 TansponeM4x4(const matrix4x4& A)
{
    matrix4x4 matrix;

    matrix.col[0].x = A.col[0].x;
    matrix.col[1].x = A.col[0].y;
    matrix.col[2].x = A.col[0].z;
    matrix.col[3].x = A.col[0].w;

    matrix.col[0].y = A.col[1].x;
    matrix.col[1].y = A.col[1].y;
    matrix.col[2].y = A.col[1].z;
    matrix.col[3].y = A.col[1].w;

    matrix.col[0].z = A.col[2].x;
    matrix.col[1].z = A.col[2].y;
    matrix.col[2].z = A.col[2].z;
    matrix.col[3].z = A.col[2].w;

    matrix.col[0].w = A.col[3].x;
    matrix.col[1].w = A.col[3].y;
    matrix.col[2].w = A.col[3].z;
    matrix.col[3].w = A.col[3].w;

    return matrix;
}

matrix4x4 InvertM4x4(const matrix4x4& A)
{
    float* m = M4x4ToArray(A);
    float inv[16], det;
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

    delete[] m;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        inv[i] *= det;

    return ArrayToM4x4(inv);
}

float4 MultiplyM4x4F4(const matrix4x4& matrix, const float4& vector)
{
    float x = vector.x*matrix.col[0].x + vector.y*matrix.col[1].x + vector.z*matrix.col[2].x + vector.w*matrix.col[3].x;
    float y = vector.x*matrix.col[0].y + vector.y*matrix.col[1].y + vector.z*matrix.col[2].y + vector.w*matrix.col[3].y;
    float z = vector.x*matrix.col[0].z + vector.y*matrix.col[1].z + vector.z*matrix.col[2].z + vector.w*matrix.col[3].z;
    float w = vector.x*matrix.col[0].w + vector.y*matrix.col[1].w + vector.z*matrix.col[2].w + vector.w*matrix.col[3].w;

    return {x, y, z, w};
}

float* M4x4ToArray(const matrix4x4& A)
{
    float* arr = new float[16];

    arr[0] = A.col[0].x;
    arr[1] = A.col[0].y;
    arr[2] = A.col[0].z;
    arr[3] = A.col[0].w;

    arr[4] = A.col[1].x;
    arr[5] = A.col[1].y;
    arr[6] = A.col[1].z;
    arr[7] = A.col[1].w;

    arr[8] = A.col[2].x;
    arr[9] = A.col[2].y;
    arr[10] = A.col[2].z;
    arr[11] = A.col[2].w;

    arr[12] = A.col[3].x;
    arr[13] = A.col[3].y;
    arr[14] = A.col[3].z;
    arr[15] = A.col[3].w;

    return arr;
}

matrix4x4 ArrayToM4x4(const float* array)
{
    matrix4x4 result;

    result.col[0] = {array[0], array[4], array[8], array[12]};
    result.col[1] = {array[1], array[5], array[9], array[13]};
    result.col[2] = {array[2], array[6], array[10], array[14]};
    result.col[3] = {array[3], array[7], array[11], array[15]};

    return result;
}

void TranslateM4x4(matrix4x4& matrix, float3 translation)
{
    matrix.col[3].x += translation.x;
    matrix.col[3].y += translation.y;
    matrix.col[3].z += translation.z;
}

void ScaleM4x4(matrix4x4& matrix, float3 scale)
{
    matrix.col[0].x = scale.x;
    matrix.col[1].y = scale.y;
    matrix.col[2].z = scale.z;
}

void RotateXM4x4(matrix4x4& matrix, float radians)
{
    float a = matrix.col[0].y;
    float b = matrix.col[0].z;
    matrix.col[0].y = a*cosf(radians) - b*sinf(radians);
    matrix.col[0].z = a*sinf(radians) + b*cosf(radians);
    a = matrix.col[1].y;
    b = matrix.col[1].z;
    matrix.col[1].y = a*cosf(radians) - b*sinf(radians);
    matrix.col[1].z = a*sinf(radians) + b*cosf(radians);
    a = matrix.col[2].y;
    b = matrix.col[2].z;
    matrix.col[2].y = a*cosf(radians) - b*sinf(radians);
    matrix.col[2].z = a*sinf(radians) + b*cosf(radians);
    a = matrix.col[3].y;
    b = matrix.col[3].z;   
    matrix.col[3].y = a*cosf(radians) - b*sinf(radians);
    matrix.col[3].z = a*sinf(radians) + b*cosf(radians);
}

void RotateYM4x4(matrix4x4& matrix, float radians)
{
    float a = matrix.col[0].x;
    float b = matrix.col[0].z;
    matrix.col[0].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[0].z = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[1].x;
    b = matrix.col[1].z;
    matrix.col[1].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[1].z = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[2].x;
    b = matrix.col[2].z;
    matrix.col[2].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[2].z = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[3].x;
    b = matrix.col[3].z;   
    matrix.col[3].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[3].z = -a*sinf(radians) + b*cosf(radians);
}

void RotateZM4x4(matrix4x4& matrix, float radians)
{
    float a = matrix.col[0].x;
    float b = matrix.col[0].y;
    matrix.col[0].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[0].y = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[1].x;
    b = matrix.col[1].y;
    matrix.col[1].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[1].y = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[2].x;
    b = matrix.col[2].y;
    matrix.col[2].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[2].y = -a*sinf(radians) + b*cosf(radians);
    a = matrix.col[3].x;
    b = matrix.col[3].y;   
    matrix.col[3].x = a*cosf(radians) + b*sinf(radians);
    matrix.col[3].y = -a*sinf(radians) + b*cosf(radians);
}

void RotateXYZM4x4(matrix4x4& matrix, float3 rotation)
{
    if(rotation.x != 0.0f)
        RotateXM4x4(matrix, rotation.x);
    if(rotation.y != 0.0f)
        RotateYM4x4(matrix, rotation.y);
    if(rotation.z != 0.0f)
        RotateZM4x4(matrix, rotation.z);
}

matrix4x4 ProjectionMatrix(int width, int height, float FOV, float near, float far)
{
    float aspectRatio = (float)width/(float)height;
    float tg = tanf(FOV*0.5f*PI/180.0f);

    matrix4x4 matrix = matrix4x4identity;

    matrix.col[0].x = 1.0f/(aspectRatio*tg);
    matrix.col[1].y = 1.0f/tg;
    matrix.col[2].z = -far/(near - far);
    matrix.col[3].z = (far*near)/(near - far);

    return matrix;
}

matrix4x4 LookAtMatrix(float3 eye, float3 target, float3 up)
{
    float3 f = SubstractF3(target, eye);
    f = NormalizeF3(f);

    float3 r = CrossProduct(f, up);
    r = {-r.x, -r.y, -r.z};
    r = NormalizeF3(r);

    float3 u = CrossProduct(r, f);
    u = {-u.x, -u.y, -u.z};

    matrix4x4 matrix;

    matrix.col[0].x = r.x;
    matrix.col[1].x = r.y;
    matrix.col[2].x = r.z;

    matrix.col[0].y = u.x;
    matrix.col[1].y = u.y;
    matrix.col[2].y = u.z;

    matrix.col[0].z = f.x;
    matrix.col[1].z = f.y;
    matrix.col[2].z = f.z;

    matrix.col[0].w = 0.0f;
    matrix.col[1].w = 0.0f;
    matrix.col[2].w = 0.0f;

    matrix.col[3].x = -DotProductF3(r,eye);
    matrix.col[3].y = -DotProductF3(u,eye);
    matrix.col[3].z = -DotProductF3(f,eye);
    matrix.col[3].w = 1.0f;

    return matrix;
}

}