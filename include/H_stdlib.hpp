#ifndef H_stdlib_HPP
#define H_stdlib_HPP

#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#ifdef DEBUG
    #define IF_DEBUG_CODE(...) __VA_ARGS__
#else
    #define IF_DEBUG_CODE(...)
#endif
#define DEBUG_CODE(code) IF_DEBUG_CODE( code )   

namespace Hero
{

}

#endif