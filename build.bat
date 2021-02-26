@echo off
echo Building realse library
g++ -c -Iinclude -Ilibs\SDL2\include -Ilibs\Glew\include source\*.cpp -lSDL2main -lSDL2 -lGLEW -lGLU -lGL
ar rcs -o lib/libHeroWin.lib *.o
del *.o