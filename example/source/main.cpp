#include"Hero.hpp"

#include"menu.hpp"

int main(int argc, char *argv[])
{
    Hero::Game game("Test", 1280, 720); // inicjalizacja systemów

    Menu* startLevel = new Menu(); // stworzenie początkowego levelu

    game.Start(startLevel); // uruchomienie silnika

    return 0;
}


















