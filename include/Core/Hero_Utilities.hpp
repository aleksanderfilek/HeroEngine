#ifndef HERO_UTILITIES_HPP
#define HERO_UtILITIES_HPP

#include<iostream>
#include<string>

#include"Core/Hero_Config.hpp"

namespace Hero
{

#ifdef DEBUG
    #define IF_DEBUG_CODE(...) __VA_ARGS__
#else
    #define IF_DEBUG_CODE(...)
#endif
#define DEBUG_CODE(code) IF_DEBUG_CODE( code )   

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

GLint glShaderCheckError_(GLuint shader, GLenum pname ,const char *file, int line);
#define glShaderCheckError(shader, type) glShaderCheckError_(shader, type, __FILE__, __LINE__) 

GLint glProgramCheckError_(GLuint program, GLenum pname ,const char *file, int line);
#define glProgramCheckError(program, type) glProgramCheckError_(program, type, __FILE__, __LINE__) 


}

#endif