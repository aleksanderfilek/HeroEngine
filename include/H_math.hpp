#ifndef HERO_MATH_HPP
#define HERO_MATH_HPP

#include <cstring>

namespace Hero{

#define PI 3.141596f

#define Min(a, b) (a > b)?b:a
#define Max(a, b) (a > b)?a:b

typedef struct int2
{
    int x,y;

    const int2 operator+ (const int2& rhs) const;
    const int2 operator- (const int2& rhs) const;
    int2& operator+= (const int2& rhs);
    int2& operator-= (const int2& rhs);
}int2;

#define int2zero {0,0}
#define int2ne {1,1}

typedef struct int4
{
    int x,y,w,h;
}int4;

typedef struct float2
{
    float x,y;
}float2;

float2 add(const float2& a, const float2& b);
float2 substract(const float2& a, const float2& b);
float2 multiply(const float2& a, float k);
float dot_product(const float2& a, const float2& b);
float length(const float2& vector);
float2 normalized(const float2& vector);
void normalize(float2& vector);

typedef struct float3
{
    float x,y,z;
}float3;

float3 add(const float3& a, const float3& b);
float3 substract(const float3& a, const float3& b);
float3 multiply(const float3& a, float k);
float dot_product(const float3& a, const float3& b);
float3 cross_product(const float3& a, const float3& b);
float length(const float3& vector);
float3 normalized(const float3& vector);
void normalize(float3& vector);

typedef float3 matrix3x3[3];

typedef struct float4
{
    float x,y,z,w;
}float4;

typedef struct
{
    float4 v[4];
}matrix4x4;

float deg2rad(float degree);
float rad2deg(float radians);

void matrix_identity(matrix4x4& matrix);
void matrix_projection(matrix4x4& matrix, int width, int height, float FOV, float near, float far);
void matrix_orthographic(matrix4x4& matrix, int width, int height, float near, float far);
void matrix_lookAt(matrix4x4& matrix, float3 eye, float3 target, float3 up);

void matrix_translate(matrix4x4& matrix, float3 translation);
void matrix_scale(matrix4x4& matrix, float3 scale);
void matrix_rotateAxisX(matrix4x4& matrix, float angle);
void matrix_rotateAxisY(matrix4x4& matrix, float angle);
void matrix_rotateAxisZ(matrix4x4& matrix, float angle);
void matrix_rotate(matrix4x4& matrix, float3 rotation);

}

#endif