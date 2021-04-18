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