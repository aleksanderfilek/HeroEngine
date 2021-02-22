@echo off
echo Building realse library
g++ -c -Iinclude source/*.cpp -lSDL2main -lSDL2 -lGLEW -lGLU -lGL
ar rcs -o lib/libHero.a *.o
rm *.o