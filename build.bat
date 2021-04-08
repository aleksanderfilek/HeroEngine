@echo off
if %1==1 (
echo Building realse library
g++ -c -D DEBUG -Iinclude  source\H_game.cpp -o H_game.o
g++ -c -D DEBUG -Iinclude  source\H_window.cpp -o H_window.o
g++ -c -D DEBUG -Iinclude  source\H_input.cpp -o H_input.o
g++ -c -D DEBUG -Iinclude  source\H_event.cpp -o H_event.o
g++ -c -D DEBUG -Iinclude  source\H_time.cpp -o H_time.o
g++ -c -D DEBUG -Iinclude  source\H_math.cpp -o H_math.o
g++ -c -D DEBUG -Iinclude  source\H_shader.cpp -o H_shader.o
g++ -c -D DEBUG -Iinclude  source\H_stdlib.cpp -o H_stdlib.o
g++ -c -D DEBUG -Iinclude  source\H_mesh.cpp -o H_mesh.o
g++ -c -D DEBUG -Iinclude  source\H_texture.cpp -o H_texture.o
g++ -c -D DEBUG -Iinclude  source\H_ui.cpp -o H_ui.o
g++ -c -D DEBUG -Iinclude  source\H_graphics.cpp -o H_graphics.o
g++ -c -D DEBUG -Iinclude  source\H_level.cpp -o H_level.o

ar rcs -o lib/libHero.lib *.o
del *.o
)

echo Build game
g++ -D DEBUG -Iinclude -Iexample\include example\source\*.cpp lib\libHero.lib -lSDL2main -lSDL2 -lSDL2_ttf -lsoil -lglew32 -lopengl32 -lglu32 