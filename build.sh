echo Building realse library
g++ -c -D ENGINE -Iinclude source/*.cpp -lSDL2main -lSDL2 -lGLEW -lGLU -lGL
ar rcs -o lib/libHero.a *.o
rm *.o


#echo Building development library
#g++ -D ENGINE -D DEBUG -c -Iinclude source/*.cpp -lSDL2main -lSDL2 -lGLEW -lGLU -lGL
#ar rcs -o lib/libHeroDev.a *.o
#rm *.o