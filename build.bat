@echo off
if %1==1 (
echo Building debug library
g++ -c -D DEBUG -Iinclude  source\Core\*.cpp 
g++ -c -D DEBUG -Iinclude  source\Systems\*.cpp

del lib\libHero.lib
ar rcs -o lib/libHero.lib *.o
)

echo Build debug game
g++ -D DEBUG -Iinclude main.cpp lib\libHero.lib -lSDL2main -lSDL2 -lSDL2_ttf -lsoil -lglew32 -lopengl32 -lglu32 