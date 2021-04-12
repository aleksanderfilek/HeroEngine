#include"worldUI.hpp"

WorldUI::WorldUI(Player*& _player):player(_player)
{
    this->font = new Hero::Font("example/resources/arial.ttf", 28);

    this->shader = new Hero::Shader();
    this->shader->Load("example/resources/shaders/uiShader.glslbin");

    this->mainGroup = new Hero::Group();

    Hero::Texture* texture1 = new Hero::Texture();
    texture1->Load("example/resources/textures/button.png");
    this->healthBackgroundImage = new Image(texture1);
    this->healthBackgroundImage->SetRelativePosition({50, 30});
    this->healthBackgroundImage->SetSize({300, 15});

    this->mainGroup->Add(this->healthBackgroundImage);

    Hero::Texture* texture2 = new Hero::Texture();
    texture2->Load("example/resources/textures/health.png");
    this->healthImage = new Image(texture2);
    this->healthImage->SetRelativePosition({50, 30});
    this->healthImage->SetSize({300, 15});

    this->mainGroup->Add(this->healthImage);

    Hero::Texture* texture3 = new Hero::Texture();
    texture3->Load("example/resources/textures/button.png");
    this->sprintBackgroundImage = new Image(texture3);
    this->sprintBackgroundImage->SetRelativePosition({50, 50});
    this->sprintBackgroundImage->SetSize({300, 15});

    this->mainGroup->Add(this->sprintBackgroundImage);

    Hero::Texture* texture4 = new Hero::Texture();
    texture4->Load("example/resources/textures/sprint.png");
    this->sprintImage = new Image(texture4);
    this->sprintImage->SetRelativePosition({50, 50});
    this->sprintImage->SetSize({300, 15});

    this->mainGroup->Add(this->sprintImage);
}

void WorldUI::Start()
{

}

void WorldUI::Update()
{
    float ratio = (float)this->player->GetHealth()/(float)this->player->GetMaxHealth();
    ratio *= 300;
    this->healthImage->SetSize({(int)ratio, 15});

    ratio = (float)this->player->GetSprint()/(float)this->player->GetMaxSprint();
    ratio *= 300;
    this->sprintImage->SetSize({(int)ratio, 15});

    this->mainGroup->Update();
}

void WorldUI::Draw()
{
    Hero::Renderer2D::SetShader(this->shader);

    this->mainGroup->Draw();
}

void WorldUI::Close()
{

}
