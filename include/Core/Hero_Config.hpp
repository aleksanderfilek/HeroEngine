#define Windows 1
#define Linux 0

#if Windows == 1
    #include<SDL\SDL.h>
    #include<GL\glew.h>
    #include<SOIL\SOIL.h>
    #include<SDL\SDL_opengl.h>
    #include<SDL\SDL_ttf.h>
    #include<GL\glu.h>
    #include<GL\gl.h>
#elif Linux == 1
    #include<SDL2/SDL.h>
    #include<GL/glew.h>
    #include<SOIL/SOIL.h>
    #include<SDL2/SDL_opengl.h>
    #include<SDL2/SDL_ttf.h>
    #include<GL/glu.h>
    #include<GL/gl.h>
#endif

#ifdef DEBUG
    #define IF_DEBUG_CODE(...) __VA_ARGS__
#else
    #define IF_DEBUG_CODE(...)
#endif
#define DEBUG_CODE(code) IF_DEBUG_CODE( code )   


GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) 