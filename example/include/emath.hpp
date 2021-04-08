#ifndef EMATH_HPP
#define EMATH_HPP

#include"Hero.hpp"

Hero::float4 matrix_vector(Hero::matrix4x4& matrix, Hero::float4& vector);
Hero::matrix4x4 matrix_matrix(Hero::matrix4x4& A, Hero::matrix4x4& B);

bool matrix_invert(const float* m, float*& invOut);
Hero::matrix4x4 ArrayToMatrix(const float* array);
float* MatrixToArray(Hero::matrix4x4& matrix);

float lerp(float a, float b, float t);
Hero::float3 Float3Lerp(const Hero::float3& p0, const Hero::float3& p1, float t);

#endif