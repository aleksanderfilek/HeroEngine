#!/bin/bash
if [ $1 -eq 1 ];
then
echo Building debug library
g++ -c -D DEBUG -Iinclude  source/Core/*.cpp
g++ -c -D DEBUG -Iinclude  source/Systems/*.cpp

rm lib/libHero.a
ar rcs -o lib/libHero.a *.o
#rm *.o
fi

echo Building debug game
g++ -D DEBUG -Iinclude main.cpp lib/libHero.a -lSDL2main -lSDL2 -lSDL2_ttf -lSOIL -lGLEW -lGL -lGLU 
