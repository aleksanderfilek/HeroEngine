#!/bin/bash
if [ $1 -eq 1 ];
then
echo Building realse library
g++ -c -D DEBUG -Iinclude  source/Core/*.cpp
g++ -c -D DEBUG -Iinclude  source/Systems/*.cpp
g++ -c -D DEBUG -Iinclude  source/*.cpp

rm lib/libHero.a
ar rcs -o lib/libHero.a *.o
rm *.o
fi

g++ -D DEBUG -Iinclude main.cpp lib/libHero.a -lSDL2main -lSDL2 -lSDL2_ttf -lsoil -lGLEW -lGL -lGLU 
