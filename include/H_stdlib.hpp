#ifndef H_stdlib_HPP
#define H_stdlib_HPP

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<GL\glew.h>
#include<iostream>
#include<string>

#ifdef DEBUG
    #define IF_DEBUG_CODE(...) __VA_ARGS__
#else
    #define IF_DEBUG_CODE(...)
#endif
#define DEBUG_CODE(code) IF_DEBUG_CODE( code )   


GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

namespace Hero
{

}

#endif