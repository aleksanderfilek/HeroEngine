#ifndef HERO_UTILITIES_H
#define HERO_UtILITIES_H

namespace Hero
{

#ifdef DEBUG
    #define IF_DEBUG_CODE(...) __VA_ARGS__
#else
    #define IF_DEBUG_CODE(...)
#endif
#define DEBUG_CODE(code) IF_DEBUG_CODE( code )   

}

#endif