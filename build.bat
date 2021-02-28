@echo off
echo Building realse library
g++ -c -Iinclude  source\H_game.cpp  -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 -o H_game.o
g++ -c -Iinclude  source\H_window.cpp  -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 -o H_window.o
g++ -c -Iinclude  source\H_input.cpp  -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 -o H_input.o
g++ -c -Iinclude  source\H_event.cpp  -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 -o H_event.o
g++ -c -Iinclude  source\H_time.cpp  -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 -o H_time.o
g++ -c -Iinclude  source\H_math.cpp  -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 -o H_math.o
g++ -c -Iinclude  source\H_shader.cpp  -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 -o H_shader.o
g++ -c -Iinclude  source\H_stdlib.cpp  -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32 -o H_stdlib.o

ar rcs -o lib/libHero.lib *.o
del *.o

g++ -Iinclude example\main.cpp lib\libHero.lib -lSDL2main -lSDL2 -lglew32 -lopengl32 -lglu32