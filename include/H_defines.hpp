#define WINDOWS 1
#define LINUX 0

#define RUNTIME_INJECTION 1
#define FPS_COUNTER 0
#define VSYNC 1

#if WINDOWS == 1
    #include<SDL\SDL.h>
    #include<GL\glew.h>
    #include<SOIL\SOIL.h>
    #include<SDL\SDL_opengl.h>
    #include<SDL\SDL_ttf.h>
    #include<GL\glu.h>
    #include<GL\gl.h>
#elif LINUX == 1
    #include<SDL2/SDL.h>
    #include<GL/glew.h>
    #include<SOIL/SOIL.h>
    #include<SDL2/SDL_opengl.h>
    #include<SDL2/SDL_ttf.h>
    #include<GL/glu.h>
    #include<GL/gl.h>
#endif
