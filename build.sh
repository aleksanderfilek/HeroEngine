#!/bin/bash
if [ $1 -eq 1 ];
then
echo Building realse library
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_game.cpp -o H_game.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_window.cpp -o H_window.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_input.cpp -o H_input.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_event.cpp -o H_event.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_time.cpp -o H_time.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_math.cpp -o H_math.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_shader.cpp -o H_shader.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_stdlib.cpp -o H_stdlib.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_mesh.cpp -o H_mesh.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_texture.cpp -o H_texture.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_ui.cpp -o H_ui.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_graphics.cpp -o H_graphics.o
g++ -c -D DEBUG -D LINUX -Iinclude  source/H_level.cpp -o H_level.o

ar rcs -o lib/libHero.a *.o
rm *.o
fi
