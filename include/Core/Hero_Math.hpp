#ifndef HERO_MATH_HPP
#define HERO_MATH_HPP

#include<cmath>

namespace Hero
{

#define PI 3.141596f

float deg2rad(float degree);
float rad2deg(float radians);

struct int2
{
    int x, y;
};

#define int2zero {0, 0}
#define int2one {1, 1}

int2 AddI2(const int2& A,const int2& B);
int2 SubstractI2(const int2& A,const int2& B);
int DotProductI2(const int2& A,const int2& B);

float DistanceI2(const int2& A, const int2& B);

struct int3
{
    int x, y, z;
};

#define int3zero {0, 0, 0}
#define int3one {1, 1, 1}

int3 AddI3(const int3& A, const int3& B);
int3 Substract(const int3& A, const int3& B);
int DotProductI3(const int3& A, const int3& B);

float DistanceI3(const int3& A, const int3& B);

struct int4
{
    int x, y, z, w;
};

#define int4zero {0, 0, 0, 0}
#define int4one {1, 1, 1, 1}

int4 AddI4(const int4& A, const int4& B);
int4 SubstractI4(const int4& A, const int4& B);

float LerpF(float a, float b, float t);

struct float2
{
    float x, y;
};

#define float2zero {0.0f, 0.0f}
#define float2one {1.0f, 1.0f}

float2 AddF2(const float2& A,const float2& B);
float2 SubstractF2(const float2& A,const float2& B);
float DotProductF2(const float2& A,const float2& B);
float2 MultiplyF2(const float2& A, float k);
float2 NormalizeF2(const float2& A);
float LengthF2(const float2& A);

float DistanceF2(const float2& A, const float2& B);

struct float3
{
    float x, y, z;
};

#define float3zero {0.0f, 0.0f, 0.0f}
#define float3one {1.0f, 1.0f, 1.0f}

float3 AddF3(const float3& A, const float3& B);
float3 SubstractF3(const float3& A, const float3& B);
float DotProductF3(const float3& A, const float3& B);
float3 CrossProduct(const float3& A, const float3& B);
float3 MultiplyF3(const float3& A, float k);
float3 NormalizeF3(const float3& A);
float LengthF3(const float3& A);
float3 LerpF3(const float3& A, const float3& B, float t);
float DistanceF3(const float3& A, const float3& B);


struct float4
{
    float x, y, z, w;
};

#define float4zero {0.0f, 0.0f, 0.0f, 0.0f}
#define float4one {1.0f, 1.0f, 1.0f, 1.0f}

float4 AddF4(const float4& A, const float4& B);
float4 SubstractF4(const float4& A, const float4& B);
float4 MultiplyF4(const float4& A, float k);
float4 NormalizeF4(const float4& A);
float LengthF4(const float4& A);

struct matrix2x2
{
    float2 col[2];
};

#define matrix2x2identity {{{1.0f,0.0f},{0.0f,1.0f}}}

matrix2x2 MultiplyM2x2(const matrix2x2& A, const matrix2x2& B);
float DeterminentM2x2(const matrix2x2& A);
matrix2x2 TansponeM2x2(const matrix2x2& A);
matrix2x2 InvertM2x2(const matrix2x2& A);

float2 MultiplyM2x2F2(const matrix2x2& matrix, const float2& vector);

struct matrix3x3
{
    float3 col[3];
};

#define matrix3x3identity {{{1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,0.0f,1.0f}}}

matrix3x3 MultiplyM3x3(const matrix3x3& A, const matrix3x3& B);
float DeterminentM3x3(const matrix3x3& A);
matrix3x3 TansponeM3x3(const matrix3x3& A);
matrix3x3 InvertM3x3(const matrix3x3& A);

float3 MultiplyM3x3F3(const matrix3x3& matrix, const float3& vector);

struct matrix4x4
{
    float4 col[4];
};

#define matrix4x4identity {{{1.0f,0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f,0.0f},{0.0f,0.0f,1.0f,0.0f},{0.0f,0.0f,0.0f,1.0f}}}

matrix4x4 MultiplyM4x4(const matrix4x4& A, const matrix4x4& B);
float DeterminentM4x4(const matrix4x4& A);
matrix4x4 TansponeM4x4(const matrix4x4& A);
matrix4x4 InvertM4x4(const matrix4x4& A);

float4 MultiplyM4x4F4(const matrix4x4& matrix, const float4& vector);

float* M4x4ToArray(const matrix4x4& A);
matrix4x4 ArrayToM4x4(const float* array);

void TranslateM4x4(matrix4x4& matrix, float3 translation);
void ScaleM4x4(matrix4x4& matrix, float3 scale);
void RotateXM4x4(matrix4x4& matrix, float radians);
void RotateYM4x4(matrix4x4& matrix, float radians);
void RotateZM4x4(matrix4x4& matrix, float radians);
void RotateXYZM4x4(matrix4x4& matrix, float3 rotation);

matrix4x4 ProjectionMatrix(int width, int height, float FOV, float near, float far);
matrix4x4 LookAtMatrix(float3 eye, float3 target, float3 up);

}

#endif