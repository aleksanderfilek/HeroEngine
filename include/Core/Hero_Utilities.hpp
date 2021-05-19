#ifndef HERO_UTILITIES_HPP
#define HERO_UTILITIES_HPP

#include<iostream>
#include<string>
#include<cstdlib>

#include"Hero_Config.hpp"

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

void ProfilerAddMemory(int size);

inline void* Allocate(size_t size)
{
    #ifdef Profile
        ProfilerAddMemory(size);
        size_t* ptr = (size_t*)std::malloc(size + 1);
        ptr[0] = size;
        ptr++;
        return (void*)ptr;
    #else
        return std::malloc(size);
    #endif
}

inline void* Callocate(size_t size)
{
    #ifdef Profile
        ProfilerAddMemory(size);
        size_t* ptr = (size_t*)std::calloc(1, size + 1);
        ptr[0] = size;
        ptr++;
        return (void*)ptr;
    #else
        return std::calloc(1, size);
    #endif
}

inline void* Reallocate(void* oldPtr, size_t size)
{
    #ifdef Profile
        size_t* oPtr = (size_t*)oldPtr;
        oPtr--;
        ProfilerAddMemory(size - oPtr[0]);
        size_t* ptr = (size_t*)std::realloc(oPtr, size + 1);
        ptr[0] = size;
        ptr++;
        return (void*)ptr;
    #else
        return std::malloc(size);
    #endif
}

inline void Delete(void* ptr)
{
    #ifdef Profile
        size_t* newptr = (size_t*)ptr;
        newptr--;
        ProfilerAddMemory(-newptr[0]);
        free((void*)newptr);
    #else
        free(ptr);
    #endif
}

}

#endif