#ifndef WORLDUI_HPP
#define WORLDUI_HPP

#include"Hero.hpp"

#include"player.hpp"
#include"uiimage.hpp"

class WorldUI: public Hero::GameObject
{
private:
    Hero::Group* mainGroup;
    Hero::Font* font;
    Hero::Shader* shader;
    Image* healthImage;
    Image* healthBackgroundImage;
    Image* sprintImage;
    Image* sprintBackgroundImage;

    Player*& player;

public:
    WorldUI(Player*& _player);

    void Start();
    void Update();
    void Draw();
    void Close();

};

#endif