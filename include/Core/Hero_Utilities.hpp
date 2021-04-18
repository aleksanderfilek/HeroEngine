#ifndef HERO_UTILITIES_HPP
#define HERO_UtILITIES_HPP

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