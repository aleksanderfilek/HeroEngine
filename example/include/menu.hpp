#ifndef MENU_HPP
#define MENU_HPP

#include"Hero.hpp"

#include"world.hpp"

class Menu:public Hero::Level
{
private:
    Hero::Group* uiGroup;
    Hero::Font* fontBig;
    Hero::Font* fontSmall;
    Hero::Shader* shader;
    Hero::Texture* btnTexture;

    event(StartBtn_Click);
    event(QuitBtn_Click);

    void OnStart() override;
    void OnUpdate() override;
    void OnDraw() override;
    void OnClose() override;
};

#endif